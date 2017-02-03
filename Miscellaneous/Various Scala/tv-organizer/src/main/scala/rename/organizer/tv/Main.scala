package rename.organizer.tv

object Main {
  def main(args: Array[String]): Unit = {
//    val listing = new Series("E:\\Guillaume\\Vidéos\\Animé\\Arrow")
//    listing findName()
    val listing = new TheTVDB
    println(listing findSeriesName "E:\\Guillaume\\Vidéos\\Séries\\Arrow\\Saison 1\\Arrow.S01E03.720p.HDTV.X264-DIMENSION")
    println(listing findSeriesName "E:\\Guillaume\\Vidéos\\Séries\\Arrow")
  }
}
