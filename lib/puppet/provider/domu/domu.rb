# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode ruby;
# kate: word-wrap-column 80; word-wrap on;

require 'puppet/resource_api'
require 'puppet/resource_api/simple_provider'

# Implementation for the domu type using the Resource API.
class Puppet::Provider::Domu::Domu < Puppet::ResourceApi::SimpleProvider
  def get(context, names = nil)
    context.info("get with #{names.inspect}")
    [
      {
        name: 'foo',
        ensure: 'present',
      },
      {
        name: 'bar',
        ensure: 'present',
      },
    ]
  end

  def set(context, changes)
    changes.each do |name, change|
      context.info("Updating '#{name}' with #{change.inspect}")
    end
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
