# Extremely basic development setup to serve the current directory at http://localhost:9001
# Start nginx in this directory with `nginx -p . -c nginx.conf`
# Stop nginx with `nginx -p . -s stop`
nginx -p . -c frontend.conf

#cd backend
#make
#./a.out
