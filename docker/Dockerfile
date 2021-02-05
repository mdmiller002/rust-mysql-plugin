FROM mysql:5.7

RUN apt-get -y update && \
apt-get -y upgrade && \
apt-get install -y build-essential && \
apt-get install -y curl

RUN curl https://sh.rustup.rs -sSf | bash -s -- -y
RUN echo 'source $HOME/.cargo/env' >> $HOME/.bashrc

RUN mkdir /src

CMD ["mysqld"]
