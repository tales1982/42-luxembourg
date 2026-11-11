FROM alpine:3.20

RUN apk add --no-cache curl bash

WORKDIR /demo
COPY run_ftp_demo.sh ./
RUN chmod +x run_ftp_demo.sh

ENTRYPOINT ["./run_ftp_demo.sh"]
