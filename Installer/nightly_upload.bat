for %%f in (IVNetwork-*.exe) do (
	curl -F "version=1.0.0" -F "type=windows-client" -F "artifact=@%%f" -F "secret=%UPLOAD_SECRET%" http://nightly.ivnetwork.tk/upload.php
)

timeout /T 5

for %%f in (IVNetworkServer-*.exe) do (
	curl -F "version=1.0.0" -F "type=windows-x86-server" -F "artifact=@%%f" -F "secret=%UPLOAD_SECRET%" http://nightly.ivnetwork.tk/upload.php
)