#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <mysql/plugin.h>
#include <mysql/plugin_auth.h>

// rust function declarations
extern int validate_password(const char *password);

/**
 * auth_simple_server is the authentication main function. This function
 * is the top-level function for the authentication work done in the plugin
 * */
static int auth_simple_server(MYSQL_PLUGIN_VIO *vio, MYSQL_SERVER_AUTH_INFO *info) {
  unsigned char *pkt;
  int pkt_len;

  // read the password as null-terminated string, fail on error
  if ((pkt_len = vio->read_packet(vio, &pkt)) < 0) {
    return CR_ERROR;
  }

  // fail on empty password
  if (!pkt_len || validate_password(pkt) != 0) {
    info->password_used = PASSWORD_USED_NO;
    return CR_ERROR;
  }

  // accept any nonempty password
  info->password_used = PASSWORD_USED_YES;
  return CR_OK;
}


/**
 * generate_auth_string_hash is used for any special hash generation needed
 * by the plugin. In our case, just copy the input password.
 * */
int generate_auth_string_hash(char *outbuf, unsigned int *buflen,
                              const char *inbuf, unsigned int inbuflen) {
  // fail if buffer specified by server cannot be copied to output buffer
  if (*buflen < inbuflen) {
    return 1;
  }
  strncpy(outbuf, inbuf, inbuflen);
  *buflen = strlen(inbuf);
  return 0;
}


/**
 * validate_auth_string_hash exists for any password validation necessary.
 * We don't need this for the auth_simple plugin.
 * */
int validate_auth_string_hash(char* const inbuf  __attribute__((unused)),
                              unsigned int buflen  __attribute__((unused))) {
  return 0;
}


/**
 * set_salt is used only by the mysql_native_password plugin. We can use
 * this trivial implementation.
 * */
int set_salt(const char* password __attribute__((unused)),
             unsigned int password_len __attribute__((unused)),
             unsigned char* salt __attribute__((unused)),
             unsigned char* salt_len)
{
  *salt_len = 0;
  return 0;
}

/**
 * MySQL authentication-specific descriptor for the plugin. This
 * struct defines the authentication-specific details of the plugin.
 * */
static struct st_mysql_auth auth_simple_handler = 
{
  MYSQL_AUTHENTICATION_INTERFACE_VERSION,
  NULL,
  auth_simple_server,
  generate_auth_string_hash,
  validate_auth_string_hash,
  set_salt,
  AUTH_FLAG_PRIVILEGED_USER_FOR_PASSWORD_CHANGE
};


/**
 * Top-level plugin descriptor for the auth_simple plugin.
 * */
mysql_declare_plugin(auth_simple)
{
  MYSQL_AUTHENTICATION_PLUGIN,
  &auth_simple_handler,
  "auth_simple",
  "Appian",
  "Authentication in rust",
  PLUGIN_LICENSE_GPL,
  NULL,
  NULL,
  0x0100,
  NULL,
  NULL,
  NULL,
  0
}
mysql_declare_plugin_end;
