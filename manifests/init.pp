# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode cstyle; word-wrap-column 140; word-wrap on;

class xen (
  Optional[String] $version = undef,
  Boolean $install = true,
  Boolean $managed = true,
  Boolean $purge = true,
  String $domain_config_dir = $::xen::paths::xen_domain_config_dir,
  String $autostart_dir = $::xen::paths::xen_autostart_dir,
  String $saved_domain_dir = $::xen::paths::saved_domain_dir,
  String $default_vif_script = 'openvswitch',
  String $default_bridge_iface = 'eth0',
  Boolean $restart_saved = true,
) inherits xen::paths  {

  $packages = ['xen', 'xen-tools', 'xen-tools-xendomains-wait-disk']
  $services = ['xencommons.service', 'xendomains.service']

  if($install)
  {
    each($packages) | $pkg | {
      unless defined(Package[$pkg]) {
        package{ $pkg:
          before => Service['xendomains.service'],
          ensure => latest,
        }
      }
    }
  }

  file { [$xendomain_systemd_dropin_dir, $xen_config_dir, $domain_config_dir, $autostart_dir, $saved_domain_dir]:
    ensure => directory,
    owner  => 'root',
    group  => 'root',
    mode   => '0755',
  }

  file { $modprobe_loopback_file:
    notify  => Reboot['critical-files-updated'],
    ensure  => file,
    owner   => 'root',
    group   => 'root',
    mode    => '0644',
    source  => 'puppet:///modules/xen/xen-loopback.conf',
  }

  file { $modules_load_xen_modules_file:
    notify  => Reboot['critical-files-updated'],
    ensure  => file,
    owner   => 'root',
    group   => 'root',
    mode    => '0644',
    source  => 'puppet:///modules/xen/xen-modules.conf',
  }

  if $restart_saved {
    file { $xendomain_systemd_dropin_file_save_dir:
      require => File[$xendomain_systemd_dropin_dir],
      before  => Service['xendomains.service'],
      ensure  => file,
      owner   => 'root',
      group   => 'root',
      mode    => '0644',
      content => epp('xen/depend-on-save-dir.conf.epp', {'domain_save_path' => $saved_domain_dir}),
    }
  }

  file { $sysconfig_xencommons_file:
    require => Package['xen'],
    ensure  => file,
    owner   => 'root',
    group   => 'root',
    mode    => '0644',
    source  => 'puppet:///modules/xen/xencommons',
  }

  file { $sysconfig_xendomains_file:
    require => Package['xen'],
    ensure  => file,
    owner   => 'root',
    group   => 'root',
    mode    => '0644',
    content => epp('xen/xendomains.epp', {'domain_save_path' => $saved_domain_dir, 'domain_autostart_path' => $autostart_dir,
      'restart_saved' => $restart_saved}),
  }

  file { $xl_config_file:
    require => Package['xen'],
    ensure  => file,
    owner   => 'root',
    group   => 'root',
    mode    => '0644',
    content => epp('xen/xl.conf.epp', {'lock_file' => $lock_file, 'default_vif_script' => $default_vif_script,
      'default_bridge_iface' => $default_bridge_iface}),
  }

  if($managed)
  {
    service { $services:
      require => [
        Package['xen'],
        File[$sysconfig_xendomains_file],
        File[$sysconfig_xencommons_file],
        File[$modules_load_xen_modules_file],
        File[$modprobe_loopback_file],
        File[$xl_config_file],
        File[$autostart_dir],
      ],
      ensure  => running,
      enable  => true,
    }
  }
}
