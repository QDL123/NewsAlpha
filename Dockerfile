FROM drogonframework/drogon

WORKDIR /app

COPY . .
RUN chmod +x ./deploy.sh

EXPOSE 8080

CMD sh ./deploy.sh && tail -f /dev/null

