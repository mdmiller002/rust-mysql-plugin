FROM mysql:5.7

RUN apt-get -y update && \
apt-get -y upgrade && \
apt-get install -y build-essential && \
apt-get install -y libmysqlclient-dev && \
apt-get install -y libmysqld-dev && \
apt-get install -y curl && \
apt-get install -y cmake

RUN curl https://sh.rustup.rs -sSf | bash -s -- -y
RUN echo 'source $HOME/.cargo/env' >> $HOME/.bashrc

RUN mkdir /code

ENV LIBMYSQL_ENABLE_CLEARTEXT_PLUGIN Y

CMD ["mysqld"]
