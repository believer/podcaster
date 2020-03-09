module.exports = {
  client: 'pg',
  dev: {
    client: 'pg',
    connection: {
      database: 'podcaster',
      user: 'postgres',
      password: 'example',
    },
    migrations: {
      tableName: 'knex_migrations',
    },
  },
}
