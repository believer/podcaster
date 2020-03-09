exports.up = async knex => {
  await knex.schema.createTable('podcast', table => {
    table
      .integer('id')
      .primary()
      .notNullable()
    table.text('title').notNullable()
    table.text('description').notNullable()
    table
      .timestamp('created_at')
      .defaultTo(knex.fn.now())
      .notNullable()
  })

  await knex.schema.createTable('episode', table => {
    table
      .integer('id')
      .primary()
      .notNullable()
    table.text('title').notNullable()
    table.text('description').notNullable()
    table.text('url').notNullable()
    table.integer('podcast_id').references('podcast.id')
    table.timestamp('air_date').notNullable()
    table
      .timestamp('created_at')
      .defaultTo(knex.fn.now())
      .notNullable()
  })
}

exports.down = async knex => {
  await knex.schema.dropTableIfExists('episode')
  await knex.schema.dropTableIfExists('podcast')
}

