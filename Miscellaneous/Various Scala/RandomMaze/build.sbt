lazy val root = (project in file(".")).settings(
  name := "Mazes",
  version := "1.0",
  scalaVersion := "2.11.6"
)

libraryDependencies += "org.scalafx" %% "scalafx" % "8.0.0-R4"
