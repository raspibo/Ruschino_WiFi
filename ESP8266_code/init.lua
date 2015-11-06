tmr.alarm(0, 3000, 0, function() dofile('web_serv.lua') end )
uart.setup(0,115200,8,0,1,0)
