# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode ruby;
# kate: word-wrap-column 80; word-wrap on;

require 'puppet/resource_api'
require 'puppet/resource_api/simple_provider'

# Implementation for the domu type using the Resource API.
class Puppet::Provider::XenDomu::XenDomu < Puppet::ResourceApi::SimpleProvider
  def get(context, name = nil)
    context.info("get with #{name.inspect}")
    [
      {
        name: name,
        ensure: 'present',
        change: 'restart',
        type: 'pv',
        pool: '',
        vcpus: 5,
        maxvcpus: 10,
        cpus: '',
        cpus_soft: '',
        cpu_weight: 100,
        cap: 100,
        memory: 1024,
        maxmem: 5120,
        on_poweroff: 'restart',
        on_reboot: 'restart',
        on_watchdog: 'restart',
        on_crash: 'restart',
        on_soft_reset: 'restart',
        kernel: '',
        ramdisk: '',
        cmdline: '',
        root: '',
        extra: '',
        firmware: '',
        pvshim: false,
        pvshim_path: '',
        pvshim_cmdline: '',
        pvshim_extra: '',
        uuid: '12345678-1234-1234-1234-0123456789ab',
        passthrough: 'disabled',
        disk: [''],
        vif: [''],
        vtpm: [''],
        vfb: [''],
        usbctrl:  '',
        usbdev: '',
        pci: '',
        pci_permissive: false,
        pci_msitranslate: false,
        pci_seize: false,
        pci_power_mgmt: false,
        gfx_passthru: false,
        vkb: '',
        bootloader: '',
        bootloader_args: '',
      },
    ]
  end

  def create(context, name, should)
    context.info("Creating '#{name}' with #{should.inspect}")
  end

  def update(context, name, should)
    context.info("Updating '#{name}' with #{should.inspect}")
  end

  def delete(context, name)
    context.info("Deleting '#{name}'")
  end
end
