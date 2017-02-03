package rename.organizer.tv

case class NotFoundException (message: String) extends Exception (message)

/** A TVScrapper to retrieve TV Show information. */
trait TVScrapper {
  /** Returns Series Name from a path. */
  def findSeriesName (path: String): String
  /** Returns Episode Name from a path (i.e. : XXX SYYEZZ). */
  def findEpisodeName (path: String): String
  /** Returns all information from an episode (abstract, ...). */
  def findEpisodeInformation (path: String): String
}