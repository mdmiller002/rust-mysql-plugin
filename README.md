# rust-mysql-plugin
A proof-of-concept of a MySQL plugin in Rust

This repository contains a simple authentication plugin for MySQL written in Rust. The plugin simply checks that a non-zero length password is
provided for the user authenticating with the plugin.

This plugin works by compiling the Rust code as a static library and linking this library into the C MySQL plugin. The Rust function is called
from the C plugin descriptor.

### Local Deployment
Docker and Docker Compose are necessary to deploy this plugin locally, with the given scripts.

1. `docker-compose up --build`
2. In another terminal, `docker-compose exec dev bash`
3. `cd /code`
4. Run `./deploy.sh` to build the Rust library, the MySQL plugin, and deploy it to the running instance of MySQL in the container.

To use the plugin:
1. Create a new user with the auth plugin
   
   `mysql> CREATE USER test_user IDENTIFIED WITH auth_simple;`
2. Log in with this user, and any non-zero length password

    `$ mysql -u test_user -p"abc"`
