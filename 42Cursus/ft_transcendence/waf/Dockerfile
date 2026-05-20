FROM owasp/modsecurity-crs:nginx-alpine

# Override the default nginx config with our custom routing rules
COPY nginx.conf /etc/nginx/templates/conf.d/default.conf.template
