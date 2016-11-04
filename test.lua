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

