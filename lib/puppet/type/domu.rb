# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode cstyle;
# kate: word-wrap-column 80; word-wrap on;

require 'puppet/resource_api'

Puppet::ResourceApi.register_type(
  name: 'domu',
  features: [ 'simple_get_filter', 'supports_noop' ],
  docs: <<-EOS,
  @summary a domu type
  @example
  domu { 'nfs-server':
    ensure      => 'present',
    type        => pv,
    pool    => 'server-pool',
    vcpu    => 2,
    maxvcpu => 4,
    cpus    => 'all',
    cpus_soft => 'all',
    cpu_weigth => 256,
    cap => 0,
    memory => 1024,
    maxmem => 2048,
    on_poweroff = destroy,
    on-reboot => restart,
    on_watchdog => destroy,
    on_crash => destroy,
    on_soft_reset => soft-reset,
    kernel => '/path/to/kernel.image',
    ramdisk => '/path/to/ram.disk',
    cmdline => '',
    root => '/dev/sda1',
    extra => '',
    firmware => 'pvgrub64',
    pvshim => false,
    pvshim_path => 'path/to/phshim',
    pvshim_cmdline
    pvshim_extra
    uuid
    passthrough
    disk
    vif
    vfb
    usbctrl
    usbdev
    pci
    pci_permissive
    pci_msitranslate
    pci_seize
    pci_power_mgmt
    gfx_passthru
    iomem
    bootloader
    bootloader_args
  }

  This type provides Puppet with the capabilities to manage ...

  If your type uses autorequires, please document as shown below, else delete
  these lines.
  **Autorequires**:
  * `Package[foo]`
  EOS
  attributes: {
    ensure: {
      type: 'Enum[present, absent]',
      desc: 'Whether this apt key should be present or absent on the target
      system.',
      default: 'present',
    },

    auto_start: {
      type: 'Boolean',
      desc: 'Whether this apt key should be present or absent on the target
      system.',
      default: 'true',
    },

    running: {
      type: 'Boolean',
      desc: 'Whether this apt key should be present or absent on the target
      system.',
      default: 'true',
    },

    name: {
      type: 'String',
      desc: 'Specifies the name of the domain. Names of domains existing on a
      single host must be unique.',
      behaviour: :namevar,
    },

    type: {
      type: 'Enum[pv, pvh, hvm]',
      desc: 'Specifies the type of domain: pv, pvh, hvm',
      default: 'pv',
        behaviour: :init_only,
    },

    pool: {
      type: 'String',
      desc: 'Put the guest\'s vCPUs into the named CPU pool.',
    },

    vcpus: {
      type: 'Integer',
      desc: 'Start the guest with N vCPUs initially online.',
      behaviour: :init_only,
    },

    maxvcpus: {
      type: 'Integer',
      desc: 'Allow the guest to bring up a maximum of M vCPUs. When starting
      the guest, if vcpus=N is less than maxvcpus=M then the first N vCPUs will
      be created online and the remainder will be created offline.',
    },

    cpus: {
      type: 'String',
      desc: 'List of host CPUs the guest is allowed to use. Default is no
      pinning at all, possible values are: "all", "0-3,5,^1",
      "nodes:0-3,^node:2"',
      default: 'all',
    },

    cpus_soft: {
      type: 'String',
      desc: 'Exactly as cpus=, but specifies soft affinity, rather than pinning
      (hard affinity). When using the credit scheduler, this means what CPUs
      the vCPUs of the domain prefer.',
    },

    cpu_weight: {
      type: 'Integer',
      desc: 'A domain with a weight of 512 will get twice as much CPU as a
      domain with a weight of 256 on a contended host. Legal weights range from
      1 to 65535 and the default is 256. Honoured by the credit and credit2
      schedulers.',
    },

    cap: {
      type: 'Integer',
      desc: 'The cap optionally fixes the maximum amount of CPU a domain will
      be able to consume, even if the host system has idle CPU cycles. The cap
      is expressed as a percentage of one physical CPU: 100 is 1 physical CPU,
      50 is half a CPU, 400 is 4 CPUs, etc. The default, 0, means there is no
      cap. Honoured by the credit and credit2 schedulers.',
    },

    memory: {
      type: 'Integer',
      desc: 'Start the guest with MBYTES megabytes of RAM.',
    },

    maxmem: {
      type: 'Integer',
      desc: 'Specifies the maximum amount of memory a guest can ever see. The
      value of maxmem= must be equal to or greater than that of memory=.',
    },

    on_poweroff: {
      type: 'Enum[destroy, restart, rename-restart, preserve, coredump-destroy,
      coredump-restart, soft-reset]',
      desc: 'Specifies what should be done with the domain if it shuts itself
      down. The default for on_poweroff is destroy.',
    },

    on_reboot: {
      type: 'Enum[destroy, restart, rename-restart, preserve, coredump-destroy,
      coredump-restart, soft-reset]',
      desc: 'Action to take if the domain shuts down with a reason code
      requesting a reboot. Default is restart.',
    },

    on_watchdog: {
      type: 'Enum[destroy, restart, rename-restart, preserve, coredump-destroy,
      coredump-restart, soft-reset]',
      desc: 'Action to take if the domain shuts down due to a Xen watchdog
      timeout. Default is destroy.',
    },

    on_crash: {
      type: 'Enum[destroy, restart, rename-restart, preserve, coredump-destroy,
      coredump-restart, soft-reset]',
      desc: 'Action to take if the domain crashes. Default is destroy.',
    },

    on_soft_reset: {
      type: 'Enum[destroy, restart, rename-restart, preserve, coredump-destroy,
      coredump-restart, soft-reset]',
      desc: 'Action to take if the domain performs a \'soft reset\' (e.g. does
      kexec). Default is soft-reset.',
    },

    kernel: {
      type: 'String',
      desc: 'Load the specified file as the kernel image.',
    },

    ramdisk: {
      type: 'String',
      desc: 'Load the specified file as the ramdisk.',
    },

    cmdline: {
      type: 'String',
      desc: 'Append STRING to the kernel command line. (Note: the meaning of
      this is guest specific). It can replace root="STRING" along with
      extra="STRING" and is preferred. When cmdline="STRING" is set,
      root="STRING" and extra="STRING" will be ignored.',
    },

    root: {
      type: 'String',
      desc: 'Append root=STRING to the kernel command line (Note: the meaning
      of this is guest specific).',
    },

    extra: {
      type: 'String',
      desc: 'Append STRING to the kernel command line. (Note: the meaning of
      this is guest specific).',
    },

    firmware: {
      type: 'Variant[Enum[pvgrub32, pvgrub64, bios, uefi, seabios, rombios,
      ovmf], String]',
      desc: 'Select the firmware to use, accepted values depend on domU type.',
    },

    pvshim: {
      type: 'Boolean',
      desc: 'Whether to boot this guest as a PV guest within a PVH container.
      Ie, the guest will experience a PV environment, but processor hardware
      extensions are used to separate its address space to mitigate the Meltdown
      attack (CVE-2017-5754).',
    },

    pvshim_path: {
      type: 'String',
      desc: 'The PV shim is a specially-built firmware-like executable
      constructed from the hypervisor source tree. This option specifies to use
      a non-default shim. Ignored if pvhsim is false.',
    },

    pvshim_cmdline: {
      type: 'String',
      desc: 'Command line for the shim. Default is "pv-shim console=xen,pv".
      Ignored if pvhsim is false.',
    },

    pvshim_extra: {
      type: 'String',
      desc: 'Extra command line arguments for the shim. If supplied, appended
      to the value for pvshim_cmdline. Default is empty. Ignored if pvhsim is
      false.',
    },

    uuid: {
      type: 'Regexp[/[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-
      [a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}/]',
      desc: 'Specifies the UUID of the domain. If not specified, a fresh unique
      UUID will be generated.',
    },

    passthrough: {
      type: 'Enum[disabled, enabled, sync_pt, sync_pt, share_pt, default]',
      desc: 'Specify whether IOMMU mappings are enabled for the domain and hence
      whether it will be enabled for passthrough hardware. Valid values for
      this option are: disabled, enabled, sync_pt, sync_pt, share_pt, default.',
    },

    disk: {
      type: 'String',
      desc: 'Specifies the disks (both emulated disks and Xen virtual block
      devices) which are to be provided to the guest, and what objects on the
      host they should map to. See xl-disk-configuration(5) for more details.',
    },

    vif: {
      type: 'String',
      desc: 'Specifies the network interfaces (both emulated network
      adapters, and Xen virtual interfaces) which are to be provided to the
      guest. See xl-network-configuration(5) for more details.',
    },

    vtpm: {
      type: 'String',
      desc: 'Specifies the Virtual Trusted Platform module to be provided to
      the guest. See xen-vtpm(7) for more details.',
    },

    vfb: {
      type: 'String',
      desc: 'Specifies the paravirtual framebuffer devices which should be
      supplied to the domain.',
    },

    usbctrl: {
      type: 'String',
      desc: 'Specifies the USB controllers created for this guest.',
    },

    usbdev: {
      type: 'String',
      desc: 'Specifies the USB devices to be attached to the guest at boot.',
    },

    pci: {
      type: 'String',
      desc: 'Specifies the host PCI devices to passthrough to this guest. Each
      PCI_SPEC_STRING has the form of
      [DDDD:]BB:DD.F[@VSLOT],KEY=VALUE,KEY=VALUE,...',
    },

    pci_permissive: {
      type: 'Boolean',
      desc: 'Changes the default value of permissive for all PCI devices passed
      through to this VM. See permissive above.',
    },

    pci_msitranslate: {
      type: 'Boolean',
      desc: 'Changes the default value of msitranslate for all PCI devices
      passed
      through to this VM. See msitranslate above.',
    },

    pci_seize: {
      type: 'Boolean',
      desc: 'Changes the default value of seize for all PCI devices passed
      through to this VM. See seize above.',
    },

    pci_power_mgmt: {
      type: 'Boolean',
      desc: '(HVM only) Changes the default value of power_mgmt for all PCI
      devices passed through to this VM. See power_mgmt above.',
    },

    gfx_passthru: {
      type: 'Variant[Boolean, String]',
      desc: 'Enable graphics device PCI passthrough. This option makes an
      assigned PCI graphics card become the primary graphics card in the VM. The
      QEMU emulated graphics adapter is disabled and the VNC console for the VM
      will not have any graphics output. All graphics output, including boot
      time QEMU BIOS messages from the VM, will go to the physical outputs of
      the passed through physical graphics card.',
    },

    vkb: {
      type: 'String',
      desc: 'Specifies the virtual keyboard device to be provided to the guest.',
    },

    bootloader: {
      type: 'String',
      desc: 'Run PROGRAM to find the kernel image and ramdisk to use. Normally
      PROGRAM would be pygrub, which is an emulation of grub/grub2/syslinux.
      Either kernel or bootloader must be specified for PV guests.',
    },

    bootloader_args: {
      type: 'String',
      desc: 'Append ARGs (presented as an array) to the arguments to the
      bootloader program',
    },
  },
  autorequire: {
    file:    '/etc/xen/config', # evaluates to the value of the `source` attribute
    package: 'xen',
  },
)
