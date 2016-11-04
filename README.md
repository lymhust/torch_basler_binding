torch-basler-binding
===================

A short binding to use basler industrial camera in torch7. Wrapper for pylon5.

Installation:
```bash
BASLER_DIR=/*path-to-pylon5-root*/ luarocks make
```
Example:

```lua
require 'basler'
require 'image'
torch.setdefaulttensortype('torch.FloatTensor')

local bs = basler.bs()

while (bs:isGrabbing()) do
	sys.tic()
	local frame = bs:retrieveResult()
	frame = frame:permute(3,1,2)
	frame = image.scale(frame, 1024, 640, 'simple')
	win = image.display{win=win, image=frame}
	print('FPS: '..1/sys.toc())
end
```
