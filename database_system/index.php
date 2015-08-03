<!DOCTYPE html>
<html lang="en">
<head> 	
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">
    <title>Proyek Akhir SBD</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link href="css/font-awesome.min.css" rel="stylesheet">
    <link href="css/prettyPhoto.css" rel="stylesheet">
    <link href="css/animate.css" rel="stylesheet">
    <link href="css/main.css" rel="stylesheet">
    <style>
		path {
		stroke: white;
		stroke-width: 0.25px;
		fill: grey;
		}
	</style>  
    <script src="http://d3js.org/d3.v3.min.js" charset="utf-8"></script>
	<script src="http://d3js.org/topojson.v1.min.js"></script>
	<script src="http://d3js.org/queue.v1.min.js"></script>
    <script src="js/grafik.js"></script>
    
    <link rel="shortcut icon" href="images/ico/favicon.ico">
    <link rel="apple-touch-icon-precomposed" sizes="144x144" href="images/ico/mobile-logo.png">
    <link rel="apple-touch-icon-precomposed" sizes="114x114" href="images/ico/mobile-logo.png">
    <link rel="apple-touch-icon-precomposed" sizes="72x72" href="images/ico/mobile-logo.png">
    <link rel="apple-touch-icon-precomposed" href="images/ico/mobile-logo.png">
</head>
<body>
    <header class="navbar navbar-inverse navbar-fixed-top wet-asphalt" role="banner">
        <div class="container">
            <div class="navbar-header">
                <a class="navbar-brand" href="index.php"><img src="images/logo.png" alt="logo"></a>
            </div>
           
        </div>
    </header>
    <section id="main-slider" class="no-margin">
        <div class="carousel slide wet-asphalt">
            <ol class="carousel-indicators">
                <li data-target="#main-slider" data-slide-to="0" class="active"></li>
            </ol>
            <div class="carousel-inner">
                <div class="item active" style="background-image: url(images/slider/bg2.jpg)">
                    <div class="container">
                        <div class="row">
                            <div class="col-sm-12">
                                <div class="carousel-content center centered">
                                    <h2 class="boxed animation animated-item-1">Hasil Produksi Mineral</h2>
                                    <br>
                                    <p class="boxed animation animated-item-2">Hasil produksi mineral Republik Indonesia dari tahun 2000 hingga 2010</p>
                                    <br>
                                    <a class="btn btn-md animation animated-item-3" href="#startGraph">Grafik</a>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
       
    </section>

    <section id="services" class="green-sea">
        <div class="container">
            <div class="row">
                <div class="col-md-4 col-sm-6">
                    <div class="media">
                        <div class="pull-left">
                            <i class="icon-calendar icon-md"></i>
                        </div>
                        <div class="media-body">
                            <h3 class="media-heading">Setiap Tahun</h3>
                            <p>Setiap tahun dari 2000 hingga 2010 hasil produksi mineral tercatat dari semua perusahaan yang ada. Dengan data ini dapat dilihat perkembangan produksi dari tahun ke tahun.</p>
                        </div>
                    </div>
                </div>
                <div class="col-md-4 col-sm-6">
                    <div class="media">
                        <div class="pull-left">
                            <i class="icon-briefcase icon-md"></i>
                        </div>
                        <div class="media-body">
                            <h3 class="media-heading">Setiap Perusahaan</h3>
                            <p>Selama 10 tahun memproduksi mineral, setiap perusahaan yang memproduksinya dapat dilihat total produksinya. Dengan ini dapat dilihat perusahaan apa yang memiliki nilai produksi tertinggi.</p>
                        </div>
                    </div>
                </div>
                <div class="col-md-4 col-sm-6">
                    <div class="media">
                        <div class="pull-left">
                            <i class="icon-globe icon-md"></i>
                        </div>
                        <div class="media-body">
                            <h3 class="media-heading">Setiap Komoditas</h3>
                            <p>Mineral di Tanah Air Indonesia ini bermacam-macam, dari keberagaman mineral yang dimiliki Indonesia dapat dilihat mineral apa yang paling banyak diproduksi.</p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section>
    

    <section id="tahun" class="clouds">
		<a id="startGraph"></a>
        <div class="container">
            <div class="row">
                <div class="col-md-10">
                    <h3>Grafik produksi mineral setiap tahun.</h3>
                    <p>Menunjukan perkembangan hasil produksi mineral setiap tahun dari 2000 hingga 2010. Dalam satuan Ton.</p>
                    <br>
                    <br>
                    <div id="grafikTahun"></div>
					<script>grafikTahun();</script>
                  </div>
             </div>
        </div>
    </section>

    <section id="perusahaan" class="clouds">
        <div class="container">
            <div class="row">
                <div class="col-lg-12">
                    <div class="center">
                        <h2>Grafik produksi mineral dari setiap perusahaan.</h2>
                        <p>Menunjukan hasil produksi selama 10 tahun dari semua perusahaan yang memproduksi mineral. Dalam satuan Ton.</p>
                        <br>
                        <br>
                        <div id="grafikPerusahaan"></div>
						<script>grafikPerusahaan();</script>
                    </div>
                    <div class="gap"></div>
                    </div>
            </div>
        </div>
    </section>
    
    <section id="komodias" class="clouds">
        <div class="container">
            <div class="row">
                <div class="col-md-8">
                    <h3>Grafik produksi mineral setiap komoditas.</h3>
                    <p>Menunjukan total produksi dari setiap komoditas yang terdapat pada Tanah Air Indonesia. Dalam satuan Ton.</p>
                    <br>
                    <br>
                    <div id="grafikMineral"></div>
					<script>grafikMineral();</script>
                    
                </div>
             </div>
        </div>
    </section>
    
    <section id="map" class="clouds">
        <div class="container">
			<div class="row">
                <div class="col-md-12 text-center">
                    <h2>Map Lokasi pertambangan di Indonesia</h2>
                                  
                    <script src="http://d3js.org/d3.v3.min.js"></script>
<script src="http://d3js.org/topojson.v0.min.js"></script>
<script>
	
	
var projection = d3.geo.mercator()
    .center([-70, -4.1])
    .scale(1400)
    .rotate([-180,0]);

var svg = d3.select("body").append("svg")
    .attr("width", "100%")
    .attr("height", 450)    
    .attr("fill", "#ecf0f1");

var path = d3.geo.path()
    .projection(projection);
    
svg.append("rect")
    .attr("width", "100%")
    .attr("height", "100%")
    .attr("fill", "#ecf0f1");
    
var g = svg.append("g")
    .attr("fill", "#ecf0f1");


// load and display the World
d3.json("data/world-110m2.json", function(error, topology) {

// load and display the cities
// d3.csv("data/cities.csv", function(error, data) {
//d3.json("data/lokasi.php", function(error, data) {
d3.json("data/lokasi.php", function(error, data) {
    g.selectAll("circle")
       .data(data)
       .enter()
       .append("a")
	   .append("circle")
       .attr("cx", function(d) {
               return projection([d.lon, d.lat])[0];
       })
       .attr("cy", function(d) {
               return projection([d.lon, d.lat])[1];
       })
       .attr("r", 3)
       .style("fill", "red");
});


g.selectAll("path")
      .data(topojson.object(topology, topology.objects.countries)
          .geometries)
    .enter()
      .append("path")
      .attr("d", path)
      
});

</script>
		                 
                </div>
            </div>
            
        </div>
    </section>
   
      
 <footer id="footer" class="midnight-blue">
        <div class="container">
            <div class="row">
                <div class="col-sm-6">
                    &copy; 2014 <a target="_blank" href="http://127.0.0.1/" title="Proyek SBD 2014">Proyek SBD</a>. All Rights Reserved.
                </div>
            </div>
        </div>
    </footer>

    <script src="js/jquery.js"></script>
    <script src="js/bootstrap.min.js"></script>
    <script src="js/jquery.prettyPhoto.js"></script>
    <script src="js/main.js"></script>
</body>
</html>
