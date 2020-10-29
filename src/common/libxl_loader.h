#include <libxl.h>

struct LibxlFunctions {
	/* Internal storage */
	GModule *_libxl_module;
	xentoollog_logger *_libxl_logger;
	libxl_ctx *_libxl_ctx;

	/* All function from libxl.h that we may possibally need */
	xentoollog_logger_stdiostream* (*xtl_createlogger_stdiostream)(FILE *f, xentoollog_level min_level, unsigned flags);
	void (*xtl_stdiostream_set_minlevel)(xentoollog_logger_stdiostream*, xentoollog_level min_level);
	void (*xtl_stdiostream_adjust_flags)(xentoollog_logger_stdiostream*, unsigned set_flags, unsigned clear_flags);
	void (*xtl_logger_destroy)(struct xentoollog_logger *logger );
	void (*xtl_logv)(struct xentoollog_logger *logger, xentoollog_level level, int errnoval, const char *context, const char *format, va_list) __attribute__((format(printf,5,0)));
	void (*xtl_log)(struct xentoollog_logger *logger, xentoollog_level level, int errnoval, const char *context, const char *format, ...) __attribute__((format(printf,5,6)));
	void (*xtl_progress)(struct xentoollog_logger *logger, const char *context, const char *doing_what, unsigned long done, unsigned long total);
	const char* (*xtl_level_to_string)(xentoollog_level);

	int (*libxl_uuid_is_nil)(const libxl_uuid *uuid);
	void (*libxl_uuid_generate)(libxl_uuid *uuid);
	int (*libxl_uuid_from_string)(libxl_uuid *uuid, const char *in);
	void (*libxl_uuid_copy)(libxl_ctx*, libxl_uuid *dst, const libxl_uuid *src);
	void (*libxl_uuid_clear)(libxl_uuid *uuid);
	int (*libxl_uuid_compare)(const libxl_uuid *uuid1, const libxl_uuid *uuid2);
	const uint8_t* (*libxl_uuid_bytearray_const)(const libxl_uuid *uuid);
	uint8_t* (*libxl_uuid_bytearray)(libxl_uuid *uuid);

	void (*libxl_mac_copy)(libxl_ctx*, libxl_mac *dst, const libxl_mac *src);

	const libxl_version_info* (*libxl_get_version_info)(libxl_ctx*);

	int (*libxl_ao_abort)(libxl_ctx*, const libxl_asyncop_how *how);
	int (*libxl_ctx_alloc)(libxl_ctx**, int version, unsigned flags, xentoollog_logger *lg);
	int (*libxl_ctx_free)(libxl_ctx*);

	int (*libxl_domain_create_new)(libxl_ctx*, libxl_domain_config *d_config, uint32_t *domid, const libxl_asyncop_how *ao_how, const libxl_asyncprogress_how *aop_console_how);
	int (*libxl_domain_create_restore)(libxl_ctx*, libxl_domain_config *d_config, uint32_t *domid, int restore_fd, int send_back_fd, const libxl_domain_restore_params *params, const libxl_asyncop_how *ao_how, const libxl_asyncprogress_how *aop_console_how);

	int (*libxl_domain_soft_reset)(libxl_ctx*, libxl_domain_config *d_config, uint32_t domid, const libxl_asyncop_how *ao_how, const libxl_asyncprogress_how *aop_console_how);
	void (*libxl_domain_config_init)(libxl_domain_config *d_config);
	void (*libxl_domain_config_dispose)(libxl_domain_config *d_config);
	int (*libxl_retrieve_domain_configuration)(libxl_ctx*, uint32_t domid, libxl_domain_config *d_config);

	int (*libxl_domain_suspend)(libxl_ctx*, uint32_t domid, int fd, int flags, const libxl_asyncop_how *ao_how);
	int (*libxl_domain_suspend_suse)(libxl_ctx*, uint32_t domid, int fd, const libxl_domain_suspend_suse_properties *props, const libxl_asyncop_how *ao_how);
	int (*libxl_domain_suspend_only)(libxl_ctx*, uint32_t domid, const libxl_asyncop_how *ao_how);
	int (*libxl_domain_resume)(libxl_ctx*, uint32_t domid, int suspend_cancel, const libxl_asyncop_how *ao_how);
	int (*libxl_domain_remus_start)(libxl_ctx*, libxl_domain_remus_info *info, uint32_t domid, int send_fd, int recv_fd, const libxl_asyncop_how *ao_how);
	int (*libxl_domain_shutdown)(libxl_ctx*, uint32_t domid);
	int (*libxl_domain_reboot)(libxl_ctx*, uint32_t domid);
	int (*libxl_domain_destroy)(libxl_ctx*, uint32_t domid, const libxl_asyncop_how *ao_how);
	int (*libxl_domain_preserve)(libxl_ctx*, uint32_t domid, libxl_domain_create_info *info, const char *name_suffix, libxl_uuid new_uuid);

	int (*libxl_get_max_cpus)(libxl_ctx*);
	int (*libxl_get_online_cpus)(libxl_ctx*);
	int (*libxl_get_max_nodes)(libxl_ctx*);

	int (*libxl_domain_rename)(libxl_ctx*, uint32_t domid, const char *old_name, const char *new_name);
	int (*libxl_domain_pause)(libxl_ctx*, uint32_t domid);
	int (*libxl_domain_unpause)(libxl_ctx*, uint32_t domid);
	int (*libxl_domain_core_dump)(libxl_ctx*, uint32_t domid, const char *filename, const libxl_asyncop_how *ao_how);
	int (*libxl_domain_setmaxmem)(libxl_ctx*, uint32_t domid, uint64_t target_memkb);

	int (*libxl_set_memory_target)(libxl_ctx*, uint32_t domid, int64_t target_memkb, int relative, int enforce);
	int (*libxl_get_memory_target)(libxl_ctx*, uint32_t domid, uint64_t *out_target);

	int (*libxl_domain_need_memory)(libxl_ctx*, const libxl_domain_build_info *b_info_in, uint64_t *need_memkb);

	int (*libxl_get_free_memory)(libxl_ctx*, uint64_t *memkb);

	int (*libxl_wait_for_free_memory)(libxl_ctx*, uint32_t domid, uint64_t memory_kb, int wait_secs);
	int (*libxl_wait_for_memory_target)(libxl_ctx*, uint32_t domid, int wait_secs);

	int (*libxl_vncviewer_exec)(libxl_ctx*, uint32_t domid, int autopass);
	int (*libxl_console_exec)(libxl_ctx*, uint32_t domid, int cons_num, libxl_console_type type, int notify_fd);
	int (*libxl_primary_console_exec)(libxl_ctx*, uint32_t domid_vm, int notify_fd);
	int (*libxl_console_get_tty)(libxl_ctx*, uint32_t domid, int cons_num, libxl_console_type type, char **path);
	int (*libxl_primary_console_get_tty)(libxl_ctx*, uint32_t domid_vm, char **path);

	int (*libxl_domain_info)(libxl_ctx*, libxl_dominfo *info_r, uint32_t domid);
	libxl_dominfo* (*libxl_list_domain)(libxl_ctx*, int *nb_domain_out);
	void (*libxl_dominfo_list_free)(libxl_dominfo *list, int nb_domain);
	libxl_cpupoolinfo* (*libxl_list_cpupool)(libxl_ctx*, int *nb_pool_out);
	void (*libxl_cpupoolinfo_list_free)(libxl_cpupoolinfo *list, int nb_pool);
	libxl_vminfo* (*libxl_list_vm)(libxl_ctx*, int *nb_vm_out);
	void (*libxl_vminfo_list_free)(libxl_vminfo *list, int nb_vm);
	libxl_cputopology* (*libxl_get_cpu_topology)(libxl_ctx*, int *nb_cpu_out);
	void (*libxl_cputopology_list_free)(libxl_cputopology *, int nb_cpu);
	libxl_pcitopology* (*libxl_get_pci_topology)(libxl_ctx*, int *num_devs);
	void (*libxl_pcitopology_list_free)(libxl_pcitopology *, int num_devs);
	libxl_numainfo* (*libxl_get_numainfo)(libxl_ctx*, int *nr);
	void (*libxl_numainfo_list_free)(libxl_numainfo *, int nr);

	libxl_vcpuinfo* (*libxl_list_vcpu)(libxl_ctx*, uint32_t domid, int *nb_vcpu, int *nr_cpus_out);
	void (*libxl_vcpuinfo_list_free)(libxl_vcpuinfo *, int nr_vcpus);

	int (*libxl_device_disk_add)(libxl_ctx*, uint32_t domid, libxl_device_disk *disk, const libxl_asyncop_how *ao_how);
	int (*libxl_device_disk_remove)(libxl_ctx*, uint32_t domid, libxl_device_disk *disk, const libxl_asyncop_how *ao_how);
	int (*libxl_device_disk_destroy)(libxl_ctx*, uint32_t domid, libxl_device_disk *disk, const libxl_asyncop_how *ao_how);
	libxl_device_disk* (*libxl_device_disk_list)(libxl_ctx*, uint32_t domid, int *num);
	void (*libxl_device_disk_list_free)(libxl_device_disk* list, int num);
	int (*libxl_device_disk_getinfo)(libxl_ctx*, uint32_t domid, libxl_device_disk *disk, libxl_diskinfo *diskinfo);

	int (*libxl_cdrom_insert)(libxl_ctx*, uint32_t domid, libxl_device_disk *disk, const libxl_asyncop_how *ao_how);
	int (*libxl_device_usbctrl_add)(libxl_ctx*, uint32_t domid, libxl_device_usbctrl *usbctrl, const libxl_asyncop_how *ao_how);
	int (*libxl_device_usbctrl_remove)(libxl_ctx*, uint32_t domid, libxl_device_usbctrl *usbctrl, const libxl_asyncop_how *ao_how);
	int (*libxl_device_usbctrl_destroy)(libxl_ctx*, uint32_t domid, libxl_device_usbctrl *usbctrl, const libxl_asyncop_how *ao_how);
	libxl_device_usbctrl* (*libxl_device_usbctrl_list)(libxl_ctx*, uint32_t domid, int *num);
	void (*libxl_device_usbctrl_list_free)(libxl_device_usbctrl *list, int nr);
	int (*libxl_device_usbctrl_getinfo)(libxl_ctx*, uint32_t domid, libxl_device_usbctrl *usbctrl, libxl_usbctrlinfo *usbctrlinfo);

	int (*libxl_device_usbdev_add)(libxl_ctx*, uint32_t domid, libxl_device_usbdev *usbdev, const libxl_asyncop_how *ao_how);
	int (*libxl_device_usbdev_remove)(libxl_ctx*, uint32_t domid, libxl_device_usbdev *usbdev, const libxl_asyncop_how *ao_how);
	libxl_device_usbdev* (*libxl_device_usbdev_list)(libxl_ctx*, uint32_t domid, int *num);
	void (*libxl_device_usbdev_list_free)(libxl_device_usbdev *list, int nr);

	int (*libxl_device_nic_add)(libxl_ctx*, uint32_t domid, libxl_device_nic *nic, const libxl_asyncop_how *ao_how);
	int (*libxl_device_nic_remove)(libxl_ctx*, uint32_t domid, libxl_device_nic *nic, const libxl_asyncop_how *ao_how);
	int (*libxl_device_nic_destroy)(libxl_ctx*, uint32_t domid, libxl_device_nic *nic, const libxl_asyncop_how *ao_how);
	libxl_device_nic* (*libxl_device_nic_list)(libxl_ctx*, uint32_t domid, int *num);
	void (*libxl_device_nic_list_free)(libxl_device_nic* list, int num);
	int (*libxl_device_nic_getinfo)(libxl_ctx*, uint32_t domid, libxl_device_nic *nic, libxl_nicinfo *nicinfo);

	libxl_device_channel* (*libxl_device_channel_list)(libxl_ctx*, uint32_t domid, int *num);
	int (*libxl_device_channel_getinfo)(libxl_ctx*, uint32_t domid, libxl_device_channel *channel, libxl_channelinfo *channelinfo);

	int (*libxl_device_vscsictrl_add)(libxl_ctx*, uint32_t domid, libxl_device_vscsictrl *vscsi, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vscsictrl_remove)(libxl_ctx*, uint32_t domid, libxl_device_vscsictrl *vscsi, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vscsictrl_destroy)(libxl_ctx*, uint32_t domid, libxl_device_vscsictrl *vscsi, const libxl_asyncop_how *ao_how);
	libxl_device_vscsictrl* (*libxl_device_vscsictrl_list)(libxl_ctx*, uint32_t domid, int *num);
	int (*libxl_device_vscsictrl_getinfo)(libxl_ctx*, uint32_t domid, libxl_device_vscsictrl *vscsictrl, libxl_device_vscsidev *vscsidev, libxl_vscsiinfo *vscsiinfo);
	int (*libxl_device_vscsidev_add)(libxl_ctx*, uint32_t domid, libxl_device_vscsidev *dev, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vscsidev_remove)(libxl_ctx*, uint32_t domid, libxl_device_vscsidev *dev, const libxl_asyncop_how *ao_how);
	void (*libxl_device_vscsictrl_append_vscsidev)(libxl_ctx*, libxl_device_vscsictrl *ctrl, libxl_device_vscsidev *dev);
	void (*libxl_device_vscsictrl_remove_vscsidev)(libxl_ctx*, libxl_device_vscsictrl *ctrl, unsigned int idx);

	int (*libxl_device_vtpm_add)(libxl_ctx*, uint32_t domid, libxl_device_vtpm *vtpm, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vtpm_remove)(libxl_ctx*, uint32_t domid, libxl_device_vtpm *vtpm, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vtpm_destroy)(libxl_ctx*, uint32_t domid, libxl_device_vtpm *vtpm, const libxl_asyncop_how *ao_how);
	libxl_device_vtpm* (*libxl_device_vtpm_list)(libxl_ctx*, uint32_t domid, int *num);
	void (*libxl_device_vtpm_list_free)(libxl_device_vtpm*, int num);
	int (*libxl_device_vtpm_getinfo)(libxl_ctx*, uint32_t domid, libxl_device_vtpm *vtpm, libxl_vtpminfo *vtpminfo);

	int (*libxl_device_vdispl_add)(libxl_ctx*, uint32_t domid, libxl_device_vdispl *displ, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vdispl_remove)(libxl_ctx*, uint32_t domid, libxl_device_vdispl *vdispl, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vdispl_destroy)(libxl_ctx*, uint32_t domid, libxl_device_vdispl *vdispl, const libxl_asyncop_how *ao_how);
	libxl_device_vdispl* (*libxl_device_vdispl_list)(libxl_ctx*, uint32_t domid, int *num);
	void (*libxl_device_vdispl_list_free)(libxl_device_vdispl* list, int num);
	int (*libxl_device_vdispl_getinfo)(libxl_ctx*, uint32_t domid, libxl_device_vdispl *vdispl, libxl_vdisplinfo *vdisplinfo);

	int (*libxl_device_vkb_add)(libxl_ctx*, uint32_t domid, libxl_device_vkb *vkb, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vkb_remove)(libxl_ctx*, uint32_t domid, libxl_device_vkb *vkb, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vkb_destroy)(libxl_ctx*, uint32_t domid, libxl_device_vkb *vkb, const libxl_asyncop_how *ao_how);

	int (*libxl_device_vfb_add)(libxl_ctx*, uint32_t domid, libxl_device_vfb *vfb, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vfb_remove)(libxl_ctx*, uint32_t domid, libxl_device_vfb *vfb, const libxl_asyncop_how *ao_how);
	int (*libxl_device_vfb_destroy)(libxl_ctx*, uint32_t domid, libxl_device_vfb *vfb, const libxl_asyncop_how *ao_how);

	int (*libxl_device_p9_remove)(libxl_ctx*, uint32_t domid, libxl_device_p9 *p9, const libxl_asyncop_how *ao_how);
	int (*libxl_device_p9_destroy)(libxl_ctx*, uint32_t domid, libxl_device_p9 *p9, const libxl_asyncop_how *ao_how);

	int (*libxl_device_pvcallsif_remove)(libxl_ctx*, uint32_t domid, libxl_device_pvcallsif *pvcallsif, const libxl_asyncop_how *ao_how);
	int (*libxl_device_pvcallsif_destroy)(libxl_ctx*, uint32_t domid, libxl_device_pvcallsif *pvcallsif, const libxl_asyncop_how *ao_how);

	int (*libxl_device_pci_add)(libxl_ctx*, uint32_t domid, libxl_device_pci *pcidev, const libxl_asyncop_how *ao_how);
	int (*libxl_device_pci_remove)(libxl_ctx*, uint32_t domid, libxl_device_pci *pcidev, const libxl_asyncop_how *ao_how);
	int (*libxl_device_pci_destroy)(libxl_ctx*, uint32_t domid, libxl_device_pci *pcidev, const libxl_asyncop_how *ao_how);
	libxl_device_pci* (*libxl_device_pci_list)(libxl_ctx*, uint32_t domid, int *num);
	int (*libxl_device_events_handler)(libxl_ctx*, const libxl_asyncop_how *ao_how);
	int (*libxl_device_pci_assignable_add)(libxl_ctx*, libxl_device_pci *pcidev, int rebind);
	int (*libxl_device_pci_assignable_remove)(libxl_ctx*, libxl_device_pci *pcidev, int rebind);
	libxl_device_pci* (*libxl_device_pci_assignable_list)(libxl_ctx*, int *num);

	int (*libxl_cpuid_parse_config)(libxl_cpuid_policy_list *cpuid, const char* str);
	int (*libxl_cpuid_parse_config_xend)(libxl_cpuid_policy_list *cpuid, const char* str);
	void (*libxl_cpuid_apply_policy)(libxl_ctx*, uint32_t domid);
	void (*libxl_cpuid_set)(libxl_ctx*, uint32_t domid, libxl_cpuid_policy_list cpuid);

	int (*libxl_userdata_store)(libxl_ctx*, uint32_t domid, const char *userdata_userid, const uint8_t *data, int datalen);
	int (*libxl_userdata_retrieve)(libxl_ctx*, uint32_t domid, const char *userdata_userid, uint8_t **data_r, int *datalen_r);
	int (*libxl_userdata_unlink)(libxl_ctx*, uint32_t domid, const char *userdata_userid);

	int (*libxl_get_physinfo)(libxl_ctx*, libxl_physinfo *physinfo);

	int (*libxl_set_vcpuaffinity)(libxl_ctx*, uint32_t domid, uint32_t vcpuid, const libxl_bitmap *cpumap_hard, const libxl_bitmap *cpumap_soft);
	int (*libxl_set_vcpuaffinity_force)(libxl_ctx*, uint32_t domid, uint32_t vcpuid, const libxl_bitmap *cpumap_hard, const libxl_bitmap *cpumap_soft);
	int (*libxl_set_vcpuaffinity_all)(libxl_ctx*, uint32_t domid, unsigned int max_vcpus, const libxl_bitmap *cpumap_hard, const libxl_bitmap *cpumap_soft);

	int (*libxl_domain_set_nodeaffinity)(libxl_ctx*, uint32_t domid, libxl_bitmap *nodemap);
	int (*libxl_domain_get_nodeaffinity)(libxl_ctx*, uint32_t domid, libxl_bitmap *nodemap);

	int (*libxl_set_vcpuonline)(libxl_ctx*, uint32_t domid, libxl_bitmap *cpumap);

	int (*libxl_get_scheduler)(libxl_ctx*);
	int (*libxl_sched_credit_params_get)(libxl_ctx*, uint32_t poolid, libxl_sched_credit_params *scinfo);
	int (*libxl_sched_credit_params_set)(libxl_ctx*, uint32_t poolid, libxl_sched_credit_params *scinfo);
	int (*libxl_sched_credit2_params_get)(libxl_ctx*, uint32_t poolid, libxl_sched_credit2_params *scinfo);
	int (*libxl_sched_credit2_params_set)(libxl_ctx*, uint32_t poolid, libxl_sched_credit2_params *scinfo);
	int (*libxl_domain_sched_params_get)(libxl_ctx*, uint32_t domid, libxl_domain_sched_params *params);
	int (*libxl_domain_sched_params_set)(libxl_ctx*, uint32_t domid, const libxl_domain_sched_params *params);

	int (*libxl_vcpu_sched_params_get)(libxl_ctx*, uint32_t domid, libxl_vcpu_sched_params *params);
	int (*libxl_vcpu_sched_params_get_all)(libxl_ctx*, uint32_t domid, libxl_vcpu_sched_params *params);
	int (*libxl_vcpu_sched_params_set)(libxl_ctx*, uint32_t domid, const libxl_vcpu_sched_params *params);
	int (*libxl_vcpu_sched_params_set_all)(libxl_ctx*, uint32_t domid, const libxl_vcpu_sched_params *params);

	int (*libxl_send_trigger)(libxl_ctx*, uint32_t domid, libxl_trigger trigger, uint32_t vcpuid);
	int (*libxl_send_sysrq)(libxl_ctx*, uint32_t domid, char sysrq);
	int (*libxl_send_debug_keys)(libxl_ctx*, char *keys);

	int (*libxl_set_parameters)(libxl_ctx*, char *params);

	libxl_xen_console_reader* (*libxl_xen_console_read_start)(libxl_ctx*, int clear);
	int (*libxl_xen_console_read_line)(libxl_ctx*, libxl_xen_console_reader *cr, char **line_r);
	void (*libxl_xen_console_read_finish)(libxl_ctx*, libxl_xen_console_reader *cr);
	uint32_t (*libxl_vm_get_start_time)(libxl_ctx*, uint32_t domid);

	char* (*libxl_tmem_list)(libxl_ctx*, uint32_t domid, int use_long);
	int (*libxl_tmem_freeze)(libxl_ctx*, uint32_t domid);
	int (*libxl_tmem_thaw)(libxl_ctx*, uint32_t domid);
	int (*libxl_tmem_set)(libxl_ctx*, uint32_t domid, char* name, uint32_t set);
	int (*libxl_tmem_shared_auth)(libxl_ctx*, uint32_t domid, char* uuid, int auth);
	int (*libxl_tmem_freeable)(libxl_ctx*);

	int (*libxl_get_freecpus)(libxl_ctx*, libxl_bitmap *cpumap);

	int (*libxl_cpupool_create)(libxl_ctx*, const char *name, libxl_scheduler sched, libxl_bitmap cpumap, libxl_uuid *uuid, uint32_t *poolid);
	int (*libxl_cpupool_destroy)(libxl_ctx*, uint32_t poolid);
	int (*libxl_cpupool_rename)(libxl_ctx*, const char *name, uint32_t poolid);
	int (*libxl_cpupool_cpuadd)(libxl_ctx*, uint32_t poolid, int cpu);
	int (*libxl_cpupool_cpuadd_node)(libxl_ctx*, uint32_t poolid, int node, int *cpus);
	int (*libxl_cpupool_cpuadd_cpumap)(libxl_ctx*, uint32_t poolid, const libxl_bitmap *cpumap);
	int (*libxl_cpupool_cpuremove)(libxl_ctx*, uint32_t poolid, int cpu);
	int (*libxl_cpupool_cpuremove_node)(libxl_ctx*, uint32_t poolid, int node, int *cpus);
	int (*libxl_cpupool_cpuremove_cpumap)(libxl_ctx*, uint32_t poolid, const libxl_bitmap *cpumap);
	int (*libxl_cpupool_movedomain)(libxl_ctx*, uint32_t poolid, uint32_t domid);
	int (*libxl_cpupool_info)(libxl_ctx*, libxl_cpupoolinfo *info, uint32_t poolid);

	int (*libxl_domid_valid_guest)(uint32_t domid);

	int (*libxl_flask_context_to_sid)(libxl_ctx*, char *buf, size_t len, uint32_t *ssidref);
	int (*libxl_flask_sid_to_context)(libxl_ctx*, uint32_t ssidref, char **buf, size_t *len);
	int (*libxl_flask_getenforce)(libxl_ctx*);
	int (*libxl_flask_setenforce)(libxl_ctx*, int mode);
	int (*libxl_flask_loadpolicy)(libxl_ctx*, void *policy, uint32_t size);

	int (*libxl_ms_vm_genid_generate)(libxl_ctx*, libxl_ms_vm_genid *id);
	_Bool (*libxl_ms_vm_genid_is_zero)(const libxl_ms_vm_genid *id);
	void (*libxl_ms_vm_genid_copy)(libxl_ctx*, libxl_ms_vm_genid *dst, const libxl_ms_vm_genid *src);

	int (*libxl_psr_cmt_attach)(libxl_ctx*, uint32_t domid);
	int (*libxl_psr_cmt_detach)(libxl_ctx*, uint32_t domid);
	int (*libxl_psr_cmt_domain_attached)(libxl_ctx*, uint32_t domid);
	int (*libxl_psr_cmt_enabled)(libxl_ctx*);
	int (*libxl_psr_cmt_get_total_rmid)(libxl_ctx*, uint32_t *total_rmid);
	int (*libxl_psr_cmt_get_l3_cache_size)(libxl_ctx*, uint32_t socketid, uint32_t *l3_cache_size);
	int (*libxl_psr_cmt_get_cache_occupancy)(libxl_ctx*, uint32_t domid, uint32_t socketid, uint32_t *l3_cache_occupancy);
	int (*libxl_psr_cmt_type_supported)(libxl_ctx*, libxl_psr_cmt_type type);
	int (*libxl_psr_cmt_get_sample)(libxl_ctx*, uint32_t domid, libxl_psr_cmt_type type, uint64_t scope, uint64_t *sample_r, uint64_t *tsc_r);
	int (*libxl_psr_cat_set_cbm)(libxl_ctx*, uint32_t domid, libxl_psr_cbm_type type, libxl_bitmap *target_map, uint64_t cbm);
	int (*libxl_psr_cat_get_cbm)(libxl_ctx*, uint32_t domid, libxl_psr_cbm_type type, uint32_t target, uint64_t *cbm_r);
	int (*libxl_psr_cat_get_info)(libxl_ctx*, libxl_psr_cat_info **info, unsigned int *nr, unsigned int lvl);
	int (*libxl_psr_cat_get_l3_info)(libxl_ctx*, libxl_psr_cat_info **info, int *nr);
	void (*libxl_psr_cat_info_list_free)(libxl_psr_cat_info *list, int nr);

	int (*libxl_psr_set_val)(libxl_ctx*, uint32_t domid, libxl_psr_type type, libxl_bitmap *target_map, uint64_t val);
	int (*libxl_psr_get_val)(libxl_ctx*, uint32_t domid, libxl_psr_type type, unsigned int target, uint64_t *val);
	int (*libxl_psr_get_hw_info)(libxl_ctx*, libxl_psr_feat_type type, unsigned int lvl, unsigned int *nr, libxl_psr_hw_info **info);
	void (*libxl_psr_hw_info_list_free)(libxl_psr_hw_info *list, unsigned int nr);
	int (*libxl_fd_set_cloexec)(libxl_ctx*, int fd, int cloexec);
	int (*libxl_fd_set_nonblock)(libxl_ctx*, int fd, int nonblock);
	int (*libxl_qemu_monitor_command)(libxl_ctx*, uint32_t domid, const char *command_line, char **output);

	int (*libxl_event_check)(libxl_ctx*, libxl_event **event_r, uint64_t typemask, libxl_event_predicate *predicate, void *predicate_user);
	int (*libxl_event_wait)(libxl_ctx*, libxl_event **event_r, uint64_t typemask, libxl_event_predicate *predicate, void *predicate_user);
	void (*libxl_event_free)(libxl_ctx*, libxl_event *event);
	void (*libxl_event_register_callbacks)(libxl_ctx*, const libxl_event_hooks *hooks, void *user);

	int (*libxl_evenable_domain_death)(libxl_ctx*, uint32_t domid, libxl_ev_user, libxl_evgen_domain_death **evgen_out);
	void (*libxl_evdisable_domain_death)(libxl_ctx*, libxl_evgen_domain_death*);

	int (*libxl_evenable_disk_eject)(libxl_ctx*, uint32_t domid, const char *vdev, libxl_ev_user, libxl_evgen_disk_eject **evgen_out);
	void (*libxl_evdisable_disk_eject)(libxl_ctx*, libxl_evgen_disk_eject*);

	int (*libxl_osevent_beforepoll)(libxl_ctx*, int *nfds_io, struct pollfd *fds, int *timeout_upd, struct timeval now);
	void (*libxl_osevent_afterpoll)(libxl_ctx*, int nfds, const struct pollfd *fds, struct timeval now);

	void (*libxl_osevent_register_hooks)(libxl_ctx*, const libxl_osevent_hooks *hooks, void *user);
	void (*libxl_osevent_occurred_fd)(libxl_ctx*, void *for_libxl, int fd, short events, short revents);
	void (*libxl_osevent_occurred_timeout)(libxl_ctx*, void *for_libxl);

	void (*libxl_childproc_setmode)(libxl_ctx*, const libxl_childproc_hooks *hooks, void *user);
	int (*libxl_childproc_reaped)(libxl_ctx*, pid_t, int status);
	void (*libxl_childproc_sigchld_occurred)(libxl_ctx*);
	void (*libxl_postfork_child_noexec)(libxl_ctx*);
};

typedef struct LibxlFunctions libxl_t;

libxl_t *libxl_load();
int libxl_init(libxl_t *xl);
int libxl_close(libxl_t *xl);
