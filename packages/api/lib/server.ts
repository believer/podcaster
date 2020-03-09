import express from 'express'
import { ApolloServer, gql, IResolvers } from 'apollo-server-express'
import merge from 'lodash.merge'
import {
  typeDefs as podcastTypeDefs,
  resolvers as podcastResolvers,
} from './resolvers/podcasts'
import {
  typeDefs as searchTypeDefs,
  resolvers as searchResolvers,
} from './resolvers/search'
import { ItunesAPI } from './datasource/itunes'
import { PodcastContext } from './types'
import { FeedAPI } from './datasource/feed'

const typeDefs = gql`
  type Query {
    hello: String
  }
`

const server = new ApolloServer({
  typeDefs: [typeDefs, podcastTypeDefs, searchTypeDefs],
  resolvers: merge(podcastResolvers, searchResolvers) as IResolvers<
    {},
    PodcastContext
  >,
  dataSources: () => ({
    feedAPI: new FeedAPI(),
    itunesAPI: new ItunesAPI(),
  }),
})

const app = express()

server.applyMiddleware({ app })

app.listen({ port: 4000 }, () =>
  console.log(`🚀 Server ready at http://localhost:4000${server.graphqlPath}`)
)
