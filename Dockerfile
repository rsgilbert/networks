# We are using a linux image that has gcc compiler
FROM node:16

WORKDIR /web 

CMD [ "mkdir", "/web" ]

CMD ["sleep", "infinity"]

