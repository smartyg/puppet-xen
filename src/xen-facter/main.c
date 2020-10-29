#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <gmodule.h>
#include <json.h>

#include "../common/libxl_loader.h"

#ifdef _
#	undef _
#endif
#define _(string) gettext(string)

#define JSON_ADD_STRING(j, k, v) json_object_object_add(j, k, json_object_new_string(v))
#define JSON_ADD_INT32(j, k, v) json_object_object_add(j, k, json_object_new_int(v))
#define JSON_ADD_INT64(j, k, v) json_object_object_add(j, k, json_object_new_int64(v))
#define JSON_ADD_UINT64(j, k, v) json_object_object_add(j, k, json_object_new_uint64(v))
#define JSON_ADD_DOUBLE(j, k, v) json_object_object_add(j, k, json_object_new_double(v))
#define JSON_ADD_BOOL(j, k, v) json_object_object_add(j, k, json_object_new_boolean(v))
#define JSON_ADD_NULL(j, k) json_object_object_add(j, k, json_object_new_null())

int add_domU(struct json_object *json, const char *id, const char *name);
int libxl_get_version(libxl_t *xl, short *major, short *minor);

int main()
{
	printf("Welcome at xen-facter\n");
	struct json_object *json;
	json = json_object_new_object();

	printf("loading libxl\n");
	libxl_t *xl = libxl_load();
	if(!libxl_init(xl))
	{
		printf("loading failed\n");
		JSON_ADD_BOOL(json, "is_dom0", 0);
		goto close_and_end;
	}
	printf("loading succeeded\n");

	JSON_ADD_BOOL(json, "is_dom0", 1);

	short major, minor;
	printf("find libxl version\n");
	libxl_get_version(xl, &major, &minor);
	JSON_ADD_INT32(json, "major", major);
	JSON_ADD_INT32(json, "minor", minor);

	add_domU(json, "1", "nfs");
	add_domU(json, "2", "db");

close_and_end:
	printf("close libxl\n");
	libxl_close(xl);

	const char *return_json = json_object_to_json_string(json);
	printf("Json string:\n");
	fputs (return_json, stdout);
	while(json_object_put(json) != 1);
	exit(EXIT_SUCCESS);
}

int libxl_get_version(libxl_t *xl, short *major, short *minor)
{
	const libxl_version_info *verInfo;

	if((verInfo = xl->libxl_get_version_info(xl->_libxl_ctx)) == NULL) return 0;

	*major = verInfo->xen_version_major;
	*minor = verInfo->xen_version_minor;
	return 1;
}

int add_domU(struct json_object *json, const char *id, const char *name)
{
    struct json_object *json_sub;
    json_sub = json_object_new_object();

    JSON_ADD_STRING(json_sub, "type", "domU");
    JSON_ADD_STRING(json_sub, "name", name);

    json_object_object_add(json, id, json_sub);

    return 1;
}
