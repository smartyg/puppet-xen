# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode ruby;
# kate: word-wrap-column 80; word-wrap on;

# Implementation for the domu type using the Resource API.
class Puppet::Provider::Domu::Domu
  def get(context, names = nil)
    context.notice("get with #{names.inspect}")
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
      context.notice("Updating '#{name}' with #{change.inspect}")
    end
  end

  def create(context, name, should)
    context.notice("Creating '#{name}' with #{should.inspect}")
  end

  def update(context, name, should)
    context.notice("Updating '#{name}' with #{should.inspect}")
  end

  def delete(context, name)
    context.notice("Deleting '#{name}'")
  end
end
