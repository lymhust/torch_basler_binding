basler = {}
local ffi = require 'ffi'

ffi.cdef[[
void init_basler(void* handle[1]);
bool IsGrabbing(void* handle[1]);	
void RetrieveResult(void* handle[1], THByteTensor* frame);
void terminate();
]]

basler.C = ffi.load(package.searchpath('libtbasler', package.cpath))
