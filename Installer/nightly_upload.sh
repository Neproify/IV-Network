pattern="IVNetworkServer-*.zip"
files=( $pattern )
file="${files[0]}"

curl -F "version=1.0.0" -F "type=linux-x86-server" -F "artifact=@$file" -F "secret=$UPLOAD_SECRET" http://nightly.ivnetwork.tk/upload.php
