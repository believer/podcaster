import { RESTDataSource, Response } from 'apollo-datasource-rest'
import { ItunesResult } from '../types'
import { SearchResult, SearchInput } from '../__generated__/graphql'

export class ItunesAPI extends RESTDataSource {
  constructor() {
    super()

    this.baseURL = 'https://itunes.apple.com/'
  }

  async parseBody(response: Response) {
    const data: {
      results: ItunesResult[]
      resultCount: number
    } = await response.json()

    return data.results.map(podcast => ({
      ...podcast,
      artist: podcast.artistName,
      artwork: podcast.artworkUrl600,
      id: podcast.collectionId,
      name: podcast.trackName,
      url: podcast.feedUrl,
    }))
  }

  async search({ limit, query }: SearchInput): Promise<SearchResult[]> {
    return this.get(`/search`, {
      term: query,
      entity: 'podcast',
      limit: limit ? limit : 10,
    })
  }

  async lookup(id: string): Promise<SearchResult> {
    const data = await this.get(`/lookup`, { id })
    return data[0]
  }
}
