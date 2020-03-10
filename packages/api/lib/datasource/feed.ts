import { RESTDataSource, Response } from 'apollo-datasource-rest'
import parser from 'fast-xml-parser'
import { Podcast } from '../__generated__/graphql'

interface Enclosure {
  '@_url': string
  '@_length': string
}

interface FeedItem {
  description: string
  enclosure: Enclosure
  'itunes:duration': string
  guid: string
  pubDate: string
  title: string
}

interface FeedImage {
  url: string
}

interface FeedEntry {
  description: string
  image: FeedImage
  item: FeedItem[]
  link: string
  title: string
}

export class FeedAPI extends RESTDataSource {
  async parseBody(response: Response) {
    const data = await response.text()

    const { description, image, item, link, title }: FeedEntry = parser.parse(
      data,
      {
        ignoreAttributes: false,
      }
    ).rss.channel

    return {
      description,
      link,
      title,
      image: image.url,
      episodes: item.map(episode => {
        return {
          date: episode.pubDate,
          description: episode.description,
          duration: episode['itunes:duration'] || episode.enclosure['@_length'],
          id: episode.guid,
          title: episode.title,
          url: episode.enclosure['@_url'],
        }
      }),
    }
  }

  async getFeed(url: string): Promise<Podcast> {
    return this.get(url)
  }
}
