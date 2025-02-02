/*
  +----------------------------------------------------------------------+
  | Copyright (c) 2010 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Andrei Zmievski <andrei@php.net>                            |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_ZOOKEEPER_H
#define PHP_ZOOKEEPER_H

#include <zookeeper.h>
#include <zookeeper_version.h>
#include <php.h>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

extern zend_module_entry zookeeper_module_entry;
#define phpext_zookeeper_ptr &zookeeper_module_entry

#ifdef PHP_WIN32
#define PHP_ZOOKEEPER_API __declspec(dllexport)
#else
#define PHP_ZOOKEEPER_API
#endif

struct php_zk_pending_marshal {
	struct php_zk_pending_marshal *next;
	struct _php_cb_data_t *cb_data;
	char is_completion;
	int type;
	int state;
	int rc;
	char *path;
};

ZEND_BEGIN_MODULE_GLOBALS(zookeeper)
	long recv_timeout;
	zend_bool session_lock;
	long sess_lock_wait;
	volatile char processing_marshal_queue;
	volatile char pending_marshals;
	struct php_zk_pending_marshal *head;
	struct php_zk_pending_marshal *tail;
ZEND_END_MODULE_GLOBALS(zookeeper)

PHP_MINIT_FUNCTION(zookeeper);
PHP_MSHUTDOWN_FUNCTION(zookeeper);
PHP_RINIT_FUNCTION(zookeeper);
PHP_RSHUTDOWN_FUNCTION(zookeeper);
PHP_MINFO_FUNCTION(zookeeper);
PHP_GINIT_FUNCTION(zookeeper);

#define PHP_ZOOKEEPER_VERSION "0.7.1"

ZEND_EXTERN_MODULE_GLOBALS(zookeeper)

#ifdef ZTS
#define ZK_G(v) TSRMG(zookeeper_globals_id, zend_zookeeper_globals *, v)
#else
#define ZK_G(v) (zookeeper_globals.v)
#endif

#ifdef HAVE_ZOOKEEPER_SESSION

#include "ext/session/php_session.h"

extern ps_module ps_mod_zookeeper;
#define ps_zookeeper_ptr &ps_mod_zookeeper

PS_FUNCS(zookeeper);

#endif /* HAVE_ZOOKEEPER_SESSION */

#endif /* PHP_ZOOKEEPER_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
