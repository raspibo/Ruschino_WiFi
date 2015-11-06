local str=wifi.ap.getmac();
local ssidTemp=string.format("%s%s%s",string.sub(str,10,11),string.sub(str,13,14),string.sub(str,16,17));
cfg={};
cfg.ssid="192.168.4.1_Ruschino-"..ssidTemp;
wifi.ap.config(cfg);
cfg.ip="192.168.4.1";
cfg.netmask="255.255.255.0";
cfg.gateway="192.168.4.1";
wifi.ap.setip(cfg);
wifi.setmode(wifi.SOFTAP)
str=nil;
ssidTemp=nil;
collectgarbage();
print("R=0&l=0&D=0&d=0&E=0&e=0")

local httpRequest={}
httpRequest["/"]="index.htm";
httpRequest["/index.htm"]="index.htm";
httpRequest["/style.css"]="style.css";

local getContentType={};
getContentType["/"]="text/html";
getContentType["/index.htm"]="text/html";
getContentType["/style.css"]="text/css";
local filePos=0;

if srv then srv:close() srv=nil end
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
    conn:on("receive", function(conn,request)
        --print("[New Request]");
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
         _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local formDATA = {}
        if (vars ~= nil)then
            --for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
            --    print("["..k.."="..v.."]");
            --    formDATA[k] = v
            --end   
            print(vars)
        end
        if getContentType[path] then
            requestFile=httpRequest[path];
        --    print("[Sending file "..requestFile.."]");            
            filePos=0;
            conn:send("HTTP/1.1 200 OK\r\nContent-Type: "..getContentType[path].."\r\n\r\n");            
        else
        --    print("[File "..path.." not found]");
            conn:send("HTTP/1.1 404 Not Found\r\n\r\n")
            conn:close();
            collectgarbage();
        end
    end)
    conn:on("sent",function(conn)
        if requestFile then
            if file.open(requestFile,r) then
                file.seek("set",filePos);
                local partial_data=file.read(512);
                file.close();
                if partial_data then
                    filePos=filePos+#partial_data;
                    --print("["..filePos.." bytes sent]");
                    conn:send(partial_data);
                    if (string.len(partial_data)==512) then
                        return;
                    end
                   
                end
            --else
            --    print("[Error opening file"..requestFile.."]");
            end
        end
        --print("[Connection closed]");
        conn:close();
        collectgarbage();
    end)
end)
