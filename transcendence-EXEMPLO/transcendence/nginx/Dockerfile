# Use the official NGINX image from Docker Hub
FROM nginx:1.21.6

# Remove the default nginx.conf
RUN rm /etc/nginx/conf.d/default.conf

# Copy the custom nginx.conf
COPY nginx.conf /etc/nginx/conf.d/

# Copy your SSL certificate and key
COPY certs/nginx-selfsigned.crt /etc/nginx/certs/
COPY certs/nginx-selfsigned.key /etc/nginx/certs/
