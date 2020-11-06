# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode cstyle; word-wrap-column 140; word-wrap on;

class xen::paths (
  String $etc_dir = '/etc',
  String $var_dir = '/var',
  String $var_lib_dir = "${var_dir}/lib",
  String $var_lock_dir = "${var_dir}/lock",
  String $sysconfig_dir = "${etc_dir}/sysconfig",
  String $systemd_dir = "${etc_dir}/systemd/system",
  String $modprobe_dir = "${etc_dir}/modprobe.d",
  String $modules_load_dir = "${etc_dir}/modules-load.d",
) {
  # --- Directories ---
  $xen_config_dir = "${etc_dir}/xen"
  $xen_domain_config_dir = "${xen_config_dir}/configs"
  $xen_autostart_dir = "${xen_config_dir}/auto"
  $xendomain_systemd_dropin_dir = "${systemd_dir}/xendomains.service.d"
  $xen_home_dir = "${var_lib_dir}/xen"
  $saved_domain_dir = "${xen_home_dir}/save"

  # --- Files ---
  $lock_file = "${var_lock_dir}/xl"
  $xendomain_systemd_dropin_file_save_dir = "${$xendomain_systemd_dropin_dir}/10-depend-on-save-dir.conf"
  $modprobe_loopback_file = "${modprobe_dir}/98-xen-loopback.conf"
  $modules_load_xen_modules_file = "${modules_load_dir}/10-xen-modules.conf"
  $sysconfig_xencommons_file = "${sysconfig_dir}/xencommons"
  $sysconfig_xendomains_file = "${sysconfig_dir}/xendomains"
  $xl_config_file = "${xen_config_dir}/xl.conf"
}
