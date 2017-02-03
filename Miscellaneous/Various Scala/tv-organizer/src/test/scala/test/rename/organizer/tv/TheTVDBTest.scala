package test.rename.organizer.tv

import org.scalatest.FlatSpec
import rename.organizer.tv.TheTVDB

class TheTVDBTest extends FlatSpec {

  "TheTVDB" must "extract Series Name from a directory" in {
    val scrapper = new TheTVDB
    assert(scrapper.findSeriesName("E:\\Guillaume\\Vidéos\\Séries\\Arrow") == "Arrow")
  }
  it must "extract name from file name" in {
    val scrapper = new TheTVDB
    assert(scrapper.findSeriesName("E:\\Guillaume\\Vidéos\\Séries\\Arrow\\Saison 1\\Arrow.S01E03.720p.HDTV.X264-DIMENSION.mkv") == "Arrow")
  }
}
