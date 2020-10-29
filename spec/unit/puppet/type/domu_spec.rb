# frozen_string_literal: true

require 'spec_helper'
require 'puppet/type/domu'

RSpec.describe 'the domu type' do
  it 'loads' do
    expect(Puppet::Type.type(:domu)).not_to be_nil
  end
end
