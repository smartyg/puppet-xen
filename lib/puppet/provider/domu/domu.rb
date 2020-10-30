# kate: replace-tabs on; indent-width 2; tab-width 2; indent-mode ruby;
# kate: word-wrap-column 80; word-wrap on;

# Implementation for the domu type using the Resource API.
class Puppet::Provider::Domu::Domu
  def get(context, _names = nil)
    context.debug('Returning pre-canned example data')
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
end
