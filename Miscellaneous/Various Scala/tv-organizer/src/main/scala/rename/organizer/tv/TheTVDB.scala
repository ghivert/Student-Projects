package rename.organizer.tv

import java.io.File

import scala.xml.{XML, Elem}

/** Scrapper for TheTVDB.
  * @constructor creates a new scrapper for the TVDB.
  */
class TheTVDB extends TVScrapper {
  /** API Key for The TVDB. */
  private val apikey = "236D91BEA19AA947"

  /** Returns Series Name. Let choose between different names if many are found.
    * Take a path and analyze if it's a directory or file to retrieve series name.*
    * @param path path to file or directory.
    * @return series name.
    */
  override def findSeriesName (path: String): String = {

    /* Construct a list of different names. */
    val exploreSeriesName =
      (x: Elem, names: List[String]) => {
        var listNames = List[String]()//names
        for (i <- x \\ "Data" \ "Series" \ "SeriesName") {
          i match {
            case <SeriesName>{seriesName}</SeriesName> => listNames = listNames ++ List[String](seriesName toString)
            case _ => throw NotFoundException("There's no serie named like that !")
          }
        }
        listNames
      }

    val name = path split File.separatorChar
    var separator = '.'
    var names = List[String]()

    val file = new File(path)
    if (file isDirectory) {
      println("Directory found. Search names...")
      val result = XML load "http://thetvdb.com/api/GetSeries.php?seriesname=" + (name(name.length - 1) split " ")(0)
      try names = names ++ exploreSeriesName(result, List())
      catch { case exception: NotFoundException => () }
    } else {
      println("File found. Search names...")
      for (i <- 1 to 4) {
        for (word <- name(name.length - 1) split separator) {
          val result = XML load "http://thetvdb.com/api/GetSeries.php?seriesname=" + word
          try names = names ++ exploreSeriesName(result, List())
          catch {
            case exception: NotFoundException => println("Bug.")
            case e: Throwable => e
          }
        }
        /* Try with different common separator names elements. */
        if (separator == '-') separator = ' '
        if (separator == '.') separator = '_'
        if (separator == '_') separator = '-'
      }
    }
    
    /* Try if names list is zero or more than 1. */
    if (names.length == 0) throw NotFoundException("No Series named like that !")
    var input = names.length + 1
    if (names.length > 1)
      while (true) {
        println("Choose the right title : ")
        var number = 1
        for (name <- names) {
          println("  " + number + ". " + name)
          number += 1
        }
        print("Enter the number of the good title : ")
        val in = Console.in
        try input = in.readLine().toInt
        catch { case e: NumberFormatException => input = name.length + 1 }
        if (input <= names.length) if (input > 0) names(input - 1)
      }
    names(0)
  }

  override def findEpisodeName(path: String): String = {

    " "
  }

  override def findEpisodeInformation(path: String): String = {
    " "
  }
}
