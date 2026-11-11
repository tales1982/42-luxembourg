FROM alpine:3.20

RUN apk add --no-cache vsftpd

RUN adduser -D -h /home/ftpuser -s /sbin/nologin ftpuser \
    && echo "ftpuser:ftppass" | chpasswd \
    && chmod 755 /home/ftpuser

COPY vsftpd.conf /etc/vsftpd/vsftpd.conf
COPY secret_report.pdf /home/ftpuser/secret_report.pdf
RUN chown ftpuser:ftpuser /home/ftpuser/secret_report.pdf

EXPOSE 21 21100-21110

CMD ["vsftpd", "/etc/vsftpd/vsftpd.conf"]
