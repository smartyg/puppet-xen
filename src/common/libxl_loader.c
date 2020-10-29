#define _GNU_SOURCE
#define LIBXL_API_VERSION 0x040200

#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <gmodule.h>
#include <libxl.h>
#include <dirent.h>
#include <string.h>

#include "libxl_loader.h"

#define _LIBXL_NAME "libxenlight.so"
#define _LIB_PATH "/usr/lib64"

#ifdef _
#	undef _
#endif
#define _(string) gettext(string)

#define LIBXL_LOAD_FUNCTION(x, f) _libxl_load_function(x->_libxl_module, #f, (gpointer *)&(x->f))

int _libxl_load_function(GModule *module, const char *function_name, gpointer *func_ptr);
char *find_library(const char *name, const char *dir);

char *find_library(const char *name, const char *dir)
{
	struct dirent **entries;
	int n;
	char *filename;

	int (*selector) (const struct dirent *) =
	({
		int __fn__ (const struct dirent *e) { return !strncmp(name, e->d_name, strlen(name)); }
		__fn__;
	});

	filename = NULL;

	n = scandir(dir, &entries, selector, versionsort);
	if(n > 0)
		asprintf(&filename, "%s/%s", dir, entries[n - 1]->d_name);

	return filename;
}

libxl_t *libxl_load()
{
	GModule *module;
	char *module_path, *filename;
	libxl_t *xl;

	//module_path = (char *)g_module_build_path(NULL, LIBXL_MODULE_NAME);
	filename = find_library(_LIBXL_NAME, _LIB_PATH);

	module = g_module_open(filename, G_MODULE_BIND_LOCAL);
	free(filename);
	filename = NULL;

	if(!module) return NULL;

	xl = malloc(sizeof(libxl_t));

	xl->_libxl_module = module;

	LIBXL_LOAD_FUNCTION(xl, xtl_createlogger_stdiostream);
	LIBXL_LOAD_FUNCTION(xl, xtl_stdiostream_set_minlevel);
	LIBXL_LOAD_FUNCTION(xl, xtl_stdiostream_adjust_flags);
	LIBXL_LOAD_FUNCTION(xl, xtl_logger_destroy);
	LIBXL_LOAD_FUNCTION(xl, xtl_logv);
	LIBXL_LOAD_FUNCTION(xl, xtl_log);
	LIBXL_LOAD_FUNCTION(xl, xtl_progress);
	LIBXL_LOAD_FUNCTION(xl, xtl_level_to_string);

	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_is_nil);
	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_generate);
	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_from_string);
	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_copy);
	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_clear);
	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_compare);
	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_bytearray_const);
	LIBXL_LOAD_FUNCTION(xl, libxl_uuid_bytearray);

	LIBXL_LOAD_FUNCTION(xl, libxl_mac_copy);

	LIBXL_LOAD_FUNCTION(xl, libxl_get_version_info);

	LIBXL_LOAD_FUNCTION(xl, libxl_ao_abort);
	LIBXL_LOAD_FUNCTION(xl, libxl_ctx_alloc);
	LIBXL_LOAD_FUNCTION(xl, libxl_ctx_free);

	LIBXL_LOAD_FUNCTION(xl, libxl_domain_create_new);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_create_restore);

	LIBXL_LOAD_FUNCTION(xl, libxl_domain_soft_reset);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_config_init);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_config_dispose);
	LIBXL_LOAD_FUNCTION(xl, libxl_retrieve_domain_configuration);

	LIBXL_LOAD_FUNCTION(xl, libxl_domain_suspend);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_suspend_suse);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_suspend_only);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_resume);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_remus_start);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_shutdown);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_reboot);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_preserve);

	LIBXL_LOAD_FUNCTION(xl, libxl_get_max_cpus);
	LIBXL_LOAD_FUNCTION(xl, libxl_get_online_cpus);
	LIBXL_LOAD_FUNCTION(xl, libxl_get_max_nodes);

	LIBXL_LOAD_FUNCTION(xl, libxl_domain_rename);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_pause);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_unpause);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_core_dump);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_setmaxmem);

	LIBXL_LOAD_FUNCTION(xl, libxl_set_memory_target);
	LIBXL_LOAD_FUNCTION(xl, libxl_get_memory_target);

	LIBXL_LOAD_FUNCTION(xl, libxl_domain_need_memory);

	LIBXL_LOAD_FUNCTION(xl, libxl_get_free_memory);

	LIBXL_LOAD_FUNCTION(xl, libxl_wait_for_free_memory);
	LIBXL_LOAD_FUNCTION(xl, libxl_wait_for_memory_target);

	LIBXL_LOAD_FUNCTION(xl, libxl_vncviewer_exec);
	LIBXL_LOAD_FUNCTION(xl, libxl_console_exec);
	LIBXL_LOAD_FUNCTION(xl, libxl_primary_console_exec);
	LIBXL_LOAD_FUNCTION(xl, libxl_console_get_tty);
	LIBXL_LOAD_FUNCTION(xl, libxl_primary_console_get_tty);

	LIBXL_LOAD_FUNCTION(xl, libxl_domain_info);
	LIBXL_LOAD_FUNCTION(xl, libxl_list_domain);
	LIBXL_LOAD_FUNCTION(xl, libxl_dominfo_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_list_cpupool);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupoolinfo_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_list_vm);
	LIBXL_LOAD_FUNCTION(xl, libxl_vminfo_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_get_cpu_topology);
	LIBXL_LOAD_FUNCTION(xl, libxl_cputopology_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_get_pci_topology);
	LIBXL_LOAD_FUNCTION(xl, libxl_pcitopology_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_get_numainfo);
	LIBXL_LOAD_FUNCTION(xl, libxl_numainfo_list_free);

	LIBXL_LOAD_FUNCTION(xl, libxl_list_vcpu);
	LIBXL_LOAD_FUNCTION(xl, libxl_vcpuinfo_list_free);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_disk_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_disk_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_disk_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_disk_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_disk_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_disk_getinfo);

	LIBXL_LOAD_FUNCTION(xl, libxl_cdrom_insert);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbctrl_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbctrl_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbctrl_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbctrl_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbctrl_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbctrl_getinfo);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbdev_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbdev_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbdev_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_usbdev_list_free);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_nic_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_nic_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_nic_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_nic_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_nic_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_nic_getinfo);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_channel_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_channel_getinfo);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsictrl_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsictrl_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsictrl_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsictrl_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsictrl_getinfo);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsidev_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsidev_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsictrl_append_vscsidev);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vscsictrl_remove_vscsidev);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_vtpm_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vtpm_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vtpm_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vtpm_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vtpm_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vtpm_getinfo);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_vdispl_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vdispl_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vdispl_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vdispl_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vdispl_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vdispl_getinfo);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_vkb_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vkb_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vkb_destroy);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_vfb_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vfb_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_vfb_destroy);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_p9_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_p9_destroy);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_pvcallsif_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_pvcallsif_destroy);

	LIBXL_LOAD_FUNCTION(xl, libxl_device_pci_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_pci_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_pci_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_pci_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_events_handler);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_pci_assignable_add);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_pci_assignable_remove);
	LIBXL_LOAD_FUNCTION(xl, libxl_device_pci_assignable_list);

	LIBXL_LOAD_FUNCTION(xl, libxl_cpuid_parse_config);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpuid_parse_config_xend);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpuid_apply_policy);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpuid_set);

	LIBXL_LOAD_FUNCTION(xl, libxl_userdata_store);
	LIBXL_LOAD_FUNCTION(xl, libxl_userdata_retrieve);
	LIBXL_LOAD_FUNCTION(xl, libxl_userdata_unlink);

	LIBXL_LOAD_FUNCTION(xl, libxl_get_physinfo);

	LIBXL_LOAD_FUNCTION(xl, libxl_set_vcpuaffinity);
	LIBXL_LOAD_FUNCTION(xl, libxl_set_vcpuaffinity_force);
	LIBXL_LOAD_FUNCTION(xl, libxl_set_vcpuaffinity_all);

	LIBXL_LOAD_FUNCTION(xl, libxl_domain_set_nodeaffinity);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_get_nodeaffinity);

	LIBXL_LOAD_FUNCTION(xl, libxl_set_vcpuonline);

	LIBXL_LOAD_FUNCTION(xl, libxl_get_scheduler);
	LIBXL_LOAD_FUNCTION(xl, libxl_sched_credit_params_get);
	LIBXL_LOAD_FUNCTION(xl, libxl_sched_credit_params_set);
	LIBXL_LOAD_FUNCTION(xl, libxl_sched_credit2_params_get);
	LIBXL_LOAD_FUNCTION(xl, libxl_sched_credit2_params_set);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_sched_params_get);
	LIBXL_LOAD_FUNCTION(xl, libxl_domain_sched_params_set);

	LIBXL_LOAD_FUNCTION(xl, libxl_vcpu_sched_params_get);
	LIBXL_LOAD_FUNCTION(xl, libxl_vcpu_sched_params_get_all);
	LIBXL_LOAD_FUNCTION(xl, libxl_vcpu_sched_params_set);
	LIBXL_LOAD_FUNCTION(xl, libxl_vcpu_sched_params_set_all);

	LIBXL_LOAD_FUNCTION(xl, libxl_send_trigger);
	LIBXL_LOAD_FUNCTION(xl, libxl_send_sysrq);
	LIBXL_LOAD_FUNCTION(xl, libxl_send_debug_keys);

	LIBXL_LOAD_FUNCTION(xl, libxl_set_parameters);

	LIBXL_LOAD_FUNCTION(xl, libxl_xen_console_read_start);
	LIBXL_LOAD_FUNCTION(xl, libxl_xen_console_read_line);
	LIBXL_LOAD_FUNCTION(xl, libxl_xen_console_read_finish);
	LIBXL_LOAD_FUNCTION(xl, libxl_vm_get_start_time);

	LIBXL_LOAD_FUNCTION(xl, libxl_tmem_list);
	LIBXL_LOAD_FUNCTION(xl, libxl_tmem_freeze);
	LIBXL_LOAD_FUNCTION(xl, libxl_tmem_thaw);
	LIBXL_LOAD_FUNCTION(xl, libxl_tmem_set);
	LIBXL_LOAD_FUNCTION(xl, libxl_tmem_shared_auth);
	LIBXL_LOAD_FUNCTION(xl, libxl_tmem_freeable);

	LIBXL_LOAD_FUNCTION(xl, libxl_get_freecpus);

	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_create);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_destroy);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_rename);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_cpuadd);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_cpuadd_node);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_cpuadd_cpumap);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_cpuremove);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_cpuremove_node);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_cpuremove_cpumap);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_movedomain);
	LIBXL_LOAD_FUNCTION(xl, libxl_cpupool_info);

	LIBXL_LOAD_FUNCTION(xl, libxl_domid_valid_guest);

	LIBXL_LOAD_FUNCTION(xl, libxl_flask_context_to_sid);
	LIBXL_LOAD_FUNCTION(xl, libxl_flask_sid_to_context);
	LIBXL_LOAD_FUNCTION(xl, libxl_flask_getenforce);
	LIBXL_LOAD_FUNCTION(xl, libxl_flask_setenforce);
	LIBXL_LOAD_FUNCTION(xl, libxl_flask_loadpolicy);

	LIBXL_LOAD_FUNCTION(xl, libxl_ms_vm_genid_generate);
	LIBXL_LOAD_FUNCTION(xl, libxl_ms_vm_genid_is_zero);
	LIBXL_LOAD_FUNCTION(xl, libxl_ms_vm_genid_copy);

	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_attach);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_detach);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_domain_attached);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_enabled);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_get_total_rmid);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_get_l3_cache_size);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_get_cache_occupancy);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_type_supported);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cmt_get_sample);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cat_set_cbm);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cat_get_cbm);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cat_get_info);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cat_get_l3_info);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_cat_info_list_free);

	LIBXL_LOAD_FUNCTION(xl, libxl_psr_set_val);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_get_val);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_get_hw_info);
	LIBXL_LOAD_FUNCTION(xl, libxl_psr_hw_info_list_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_fd_set_cloexec);
	LIBXL_LOAD_FUNCTION(xl, libxl_fd_set_nonblock);
	LIBXL_LOAD_FUNCTION(xl, libxl_qemu_monitor_command);

	LIBXL_LOAD_FUNCTION(xl, libxl_event_check);
	LIBXL_LOAD_FUNCTION(xl, libxl_event_wait);
	LIBXL_LOAD_FUNCTION(xl, libxl_event_free);
	LIBXL_LOAD_FUNCTION(xl, libxl_event_register_callbacks);

	LIBXL_LOAD_FUNCTION(xl, libxl_evenable_domain_death);
	LIBXL_LOAD_FUNCTION(xl, libxl_evdisable_domain_death);

	LIBXL_LOAD_FUNCTION(xl, libxl_evenable_disk_eject);
	LIBXL_LOAD_FUNCTION(xl, libxl_evdisable_disk_eject);

	LIBXL_LOAD_FUNCTION(xl, libxl_osevent_beforepoll);
	LIBXL_LOAD_FUNCTION(xl, libxl_osevent_afterpoll);

	LIBXL_LOAD_FUNCTION(xl, libxl_osevent_register_hooks);
	LIBXL_LOAD_FUNCTION(xl, libxl_osevent_occurred_fd);
	LIBXL_LOAD_FUNCTION(xl, libxl_osevent_occurred_timeout);

	LIBXL_LOAD_FUNCTION(xl, libxl_childproc_setmode);
	LIBXL_LOAD_FUNCTION(xl, libxl_childproc_reaped);
	LIBXL_LOAD_FUNCTION(xl, libxl_childproc_sigchld_occurred);
	LIBXL_LOAD_FUNCTION(xl, libxl_postfork_child_noexec);

	return xl;
}

int libxl_init(libxl_t *xl)
{

	xl->_libxl_logger = (xentoollog_logger *) xl->xtl_createlogger_stdiostream(stderr, XTL_PROGRESS, 0);
	if(!xl->_libxl_logger) {
		return 0;
	}

	if (xl->libxl_ctx_alloc(&(xl->_libxl_ctx), LIBXL_VERSION, 0, xl->_libxl_logger)) {
		return 0;
	}
	return 1;
}

int libxl_close(libxl_t *xl)
{
	if(g_module_close(xl->_libxl_module))
	{
		free(xl);
		return 1;
	}
	return 0;
}

int _libxl_load_function(GModule *module, const char *function_name, gpointer *func_ptr)
{
	GError **error;
	if(!g_module_symbol(module, function_name, func_ptr))
	{
		g_set_error(error, 4, 2, "%s", g_module_error());
		if(!g_module_close(module)) g_warning("%s", g_module_error());
		func_ptr = NULL;
		return 0;
	}
	return 1;
};
