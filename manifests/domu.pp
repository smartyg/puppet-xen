# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode cstyle; word-wrap-column 140; word-wrap on;

define xen::domu (
  Xen::Type $type = 'pv',
  Integer $autostart_order = 50,
  Enum['present', 'absent'] $state = 'present',
  Boolean $auto_start = true,
  Xen::Change $change = 'restart',
  Boolean $running = true,
  Optional[String] $pool = undef,
  Optional[Integer] $vcpus = undef,
  Optional[Integer] $maxvcpus = undef,
  Optional[String] $cpus = undef,
  Optional[String] $cpus_soft = undef,
  Optional[Integer] $cpu_weight = undef,
  Optional[Integer] $cap = undef,
  Optional[Integer] $memory = undef,
  Optional[Integer] $maxmem = undef,
  Optional[Xen::Action] $on_poweroff = undef,
  Optional[Xen::Action] $on_reboot = undef,
  Optional[Xen::Action] $on_watchdog = undef,
  Optional[Xen::Action] $on_crash = undef,
  Optional[Xen::Action] $on_soft_reset = undef,
  Optional[String] $kernel = undef,
  Optional[String] $ramdisk = undef,
  Optional[String] $cmdline = undef,
  Optional[String] $root = undef,
  Optional[String] $extra = undef,
  Optional[Variant[Xen::Firmware, String]] $firmware = undef,
  Optional[Boolean] $pvshim = undef,
  Optional[String] $pvshim_path = undef,
  Optional[String] $pvshim_cmdline = undef,
  Optional[String] $pvshim_extra = undef,
  Xen::Uuid $uuid,
  Optional[Xen::Passthrough] $passthrough = undef,
  Optional[Array[String]] $disk = undef,
  Optional[Array[String]] $vif = undef,
  Optional[Array[String]] $vtpm = undef,
  Optional[Array[String]] $vfb = undef,
  Optional[String] $usbctrl = undef,
  Optional[String] $usbdev = undef,
  Optional[String] $pci = undef,
  Optional[Boolean] $pci_permissive = undef,
  Optional[Boolean] $pci_msitranslate = undef,
  Optional[Boolean] $pci_seize = undef,
  Optional[Boolean] $pci_power_mgmt = undef,
  Optional[Variant[Boolean, String]] $gfx_passthru = undef,
  Optional[String] $vkb = undef,
  Optional[String] $bootloader = undef,
  Optional[String] $bootloader_args = undef,
) {
  if defined(Class['xen']) {
    include xen

    $xen_domu_config_dir = $::xen::domain_config_dir
    $xen_domu_autostart_dir = $::xen::autostart_dir

    $domu_config_file = "${xen_domu_config_dir}/${name}"
    $domu_autostart_file = "${xen_domu_autostart_dir}/${autostart_order}-${name}"

    if $disk {
      $disk_real_tmp = join($disk, '", "')
      $disk_real = "\"${disk_real_tmp}\""
    } else {
      $disk_real = undef
    }

    if $vif {
      $vif_real_tmp = join($vif, '", "')
      $vif_real = "\"${vif_real_tmp}\""
    } else {
      $vif_real = undef
    }

    if $vfb {
      $vfb_real_tmp = join($vfb, '", "')
      $vfb_real = "\"${vfb_real_tmp}\""
    } else {
      $vfb_real = undef
    }

    if $vtpm {
      $vtpm_real_tmp = join($vtpm, '", "')
      $vtpm_real = "\"${vtpm_real_tmp}\""
    } else {
      $vtpm_real = undef
    }

    file { $domu_config_file:
      ensure => file,
      owner  => 'root',
      group  => 'root',
      mode   => '0640',
      content => epp('xen/domu_config.epp',
        {
          'name'             => $name,
          'type'             => $type,
          'pool'             => $pool,
          'vcpus'            => $vcpus,
          'maxvcpus'         => $maxvcpus,
          'cpus'             => $cpus,
          'cpus_soft'        => $cpus_soft,
          'cpu_weight'       => $cpu_weight,
          'cap'              => $cap,
          'memory'           => String($memory),
          'maxmem'           => String($maxmem),
          'on_poweroff'      => $on_poweroff,
          'on_reboot'        => $on_reboot,
          'on_watchdog'      => $on_watchdog,
          'on_crash'         => $on_crash,
          'on_soft_reset'    => $on_soft_reset,
          'kernel'           => $kernel,
          'ramdisk'          => $ramdisk,
          'cmdline'          => $cmdline,
          'root'             => $root,
          'extra'            => $extra,
          'firmware'         => $firmware,
          'pvshim'           => $pvshim,
          'pvshim_path'      => $pvshim_path,
          'pvshim_cmdline'   => $pvshim_cmdline,
          'pvshim_extra'     => $pvshim_extra,
          'uuid'             => $uuid,
          'passthrough'      => $passthrough,
          'disk'             => "[ ${disk_real} ]",
          'vif'              => "[ ${vif_real} ]",
          'vtpm'             => "[ ${vtpm_real} ] ",
          'vfb'              => "[ ${vfb_real} ]",
          'usbctrl'          => $usbctrl,
          'usbdev'           => $usbdev,
          'pci'              => $pci,
          'pci_permissive'   => $pci_permissive,
          'pci_msitranslate' => $pci_msitranslate,
          'pci_seize'        => $pci_seize,
          'pci_power_mgmt'   => $pci_power_mgmt,
          'gfx_passthru'     => $gfx_passthru,
          'vkb'              => $vkb,
          'bootloader'       => $bootloader,
          'bootloader_args'  => $bootloader_args,
        }),
    }

    if $auto_start {
      file { $domu_autostart_file:
        ensure => link,
        target => $domu_config_file,
      }
    }

    # Do if any of these apply:
    # - is running and state is state is 'absent'
    # - is running and change is not 'no'
    # - if not running and state is running

    if (($name in $facts['xen']['domu_by_name'] and ($change != 'no' or $state == 'absent')) or
      (! $name in $facts['xen']['domu_by_name'] and $state == 'running')) {
      notice('Try to update running domU')
      xen_domu { $name:
        ensure           => $state,
        type             => $type,
#       change           => $change,
        pool             => $pool,
        vcpus            => $vcpus,
        maxvcpus         => $maxvcpus,
        cpus             => $cpus,
        cpus_soft        => $cpus_soft,
        cpu_weight       => $cpu_weight,
        cap              => $cap,
        memory           => $memory,
        maxmem           => $maxmem,
        on_poweroff      => $on_poweroff,
        on_reboot        => $on_reboot,
        on_watchdog      => $on_watchdog,
        on_crash         => $on_crash,
        on_soft_reset    => $on_soft_reset,
        kernel           => $kernel,
        ramdisk          => $ramdisk,
        cmdline          => $cmdline,
        root             => $root,
        extra            => $extra,
        firmware         => $firmware,
        pvshim           => $pvshim,
        pvshim_path      => $pvshim_path,
        pvshim_cmdline   => $pvshim_cmdline,
        pvshim_extra     => $pvshim_extra,
        uuid             => $uuid,
        passthrough      => $passthrough,
        disk             => $disk,
        vif              => $vif,
        vtpm             => $vtpm,
        vfb              => $vfb,
        usbctrl          => $usbctrl,
        usbdev           => $usbdev,
        pci              => $pci,
        pci_permissive   => $pci_permissive,
        pci_msitranslate => $pci_msitranslate,
        pci_seize        => $pci_seize,
        pci_power_mgmt   => $pci_power_mgmt,
        gfx_passthru     => $gfx_passthru,
        vkb              => $vkb,
        bootloader       => $bootloader,
        bootloader_args  => $bootloader_args,
      }
    }
  } else {
    err("Class `xenserver` is not declared, can not add domu ${name}")
  }
}
