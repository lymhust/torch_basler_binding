local bs = torch.class('basler.bs')
local ffi = require 'ffi'
local C = basler.C

function bs:__init()

	self.handle = ffi.new'void*[1]'
	local old_handle = self.handle[1]
    C.init(self.handle)	
	if(self.handle[1] == old_handle) then
		print 'Unsuccessful init'
	end

	self.frame = torch.ByteTensor(1200, 1920, 3)
end


function bs:isGrabbing()
	return C.IsGrabbing(self.handle)
end


function bs:retrieveResult()
	C.RetrieveResult(self.handle, self.frame:cdata())
	return self.frame
end


function bs:terminate()
	C.terminate()
end
