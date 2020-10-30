#define _GNU_SOURCE

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

int list_all_domains(libxl_t *xl, struct json_object *json);
const char *uuid_to_string(unsigned char uuid[16]);
const char *get_domain_type(libxl_domain_type t);
uint8_t get_domain_state(uint8_t running, uint8_t blocked, uint8_t paused, uint8_t shutdown, uint8_t dying, uint8_t never_stop);
int add_domU(struct json_object *json, uint32_t id, const char *name, const char *uuid, const char *type, uint32_t state, uint64_t memory, uint64_t cpu_time, uint32_t vcpus, uint32_t cpu_pool);
int libxl_get_version(libxl_t *xl, short *major, short *minor);

int main()
{
	const char *return_json;
	struct json_object *json;
	libxl_t *xl;

	json = json_object_new_object();

	if((xl = libxl_load()) == NULL)
	{
		JSON_ADD_BOOL(json, "is_dom0", 0);
		goto only_end;
	}

	if(!libxl_init(xl))
	{
		JSON_ADD_BOOL(json, "is_dom0", 0);
		goto close_and_end;
	}

	JSON_ADD_BOOL(json, "is_dom0", 1);

	short major, minor;
	libxl_get_version(xl, &major, &minor);
	JSON_ADD_INT32(json, "major", major);
	JSON_ADD_INT32(json, "minor", minor);

	list_all_domains(xl, json);

close_and_end:
	libxl_close(xl);
only_end:
	return_json = json_object_to_json_string(json);
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

int list_all_domains(libxl_t *xl, struct json_object *json)
{
	int n_domains = 0;
	libxl_dominfo *info;
	info = xl->libxl_list_domain(xl->_libxl_ctx, &n_domains);
	if(n_domains > 0)
	{
		for(int n = 0; n < n_domains; n++)
		{
			const char *name = NULL;
			libxl_dominfo i = info[n];
			const char *uuid = uuid_to_string((i.uuid).uuid);
			const char *type = get_domain_type(i.domain_type);
			uint8_t state = get_domain_state((uint8_t)i.running, (uint8_t)i.blocked, (uint8_t)i.paused, (uint8_t)i.shutdown, (uint8_t)i.dying, (uint8_t)i.never_stop);

			if(n > 0)
			{
				libxl_domain_config d_config;
				xl->libxl_retrieve_domain_configuration(xl->_libxl_ctx, i.domid, &d_config);
				name = d_config.c_info.name;
			}

			add_domU(json, (uint32_t)(i.domid), name, uuid, type, (uint32_t)state, i.current_memkb, i.cpu_time, i.vcpu_online, i.cpupool);
		}
	}
	xl->libxl_dominfo_list_free(info, n_domains);
}

const char *uuid_to_string(unsigned char uuid[16])
{
	char *str = malloc(37);
	sprintf(str, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7], uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
	return str;
}

const char *get_domain_type(libxl_domain_type t)
{
	if(t == LIBXL_DOMAIN_TYPE_HVM)
		return "hvm";
	else if(t == LIBXL_DOMAIN_TYPE_PV)
		return "pv";
	else if(t == LIBXL_DOMAIN_TYPE_PVH)
		return "pvh";
	else
		return "unknown";
}

uint8_t get_domain_state(uint8_t running, uint8_t blocked, uint8_t paused, uint8_t shutdown, uint8_t dying, uint8_t never_stop)
{
	uint8_t state = 0;
	state |= running << 0;
	state |= blocked << 1;
	state |= paused << 2;
	state |= shutdown << 3;
	state |= dying << 4;
	state |= never_stop << 5;
	return state;
}

int add_domU(struct json_object *json, uint32_t id, const char *name, const char *uuid, const char *type, uint32_t state, uint64_t memory, uint64_t cpu_time, uint32_t vcpus, uint32_t cpu_pool)
{
	char *id_string;
    struct json_object *json_sub;
    json_sub = json_object_new_object();

	JSON_ADD_INT32(json_sub, "id", id);
	if(name != NULL)
		JSON_ADD_STRING(json_sub, "name", name);
	JSON_ADD_STRING(json_sub, "uuid", uuid);
	JSON_ADD_STRING(json_sub, "type", type);
	JSON_ADD_INT32(json_sub, "state", state);
	JSON_ADD_INT64(json_sub, "memory", memory);
	JSON_ADD_INT64(json_sub, "cpu_time", cpu_time);
	JSON_ADD_INT32(json_sub, "vcpus", vcpus);
	JSON_ADD_INT32(json_sub, "cpu_pool", cpu_pool);

	asprintf(&id_string, "%u", id);
	json_object_object_add(json, id_string, json_sub);
	free(id_string);

    return 1;
}
