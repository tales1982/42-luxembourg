<?php

 define( 'DB_NAME', 'wordpress_db' );
 define( 'DB_USER', 'wp_user' );
 define( 'DB_PASSWORD', '123456' );
 define( 'DB_HOST', 'mariadb:3306' );
 define( 'WP_DEBUG_LOG', true );#para debugar no terminal usando o docker desktop
 
if ( ! defined( 'ABSPATH' ) ) {
    define( 'ABSPATH', __DIR__ . '/' );
}

require_once ABSPATH . 'wp-settings.php';
?>