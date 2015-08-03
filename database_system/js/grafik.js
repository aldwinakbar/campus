
// Mengambil data yang berformat json dari suatu file php, file php ini nantinya akan mengambil data-data dari database
var data = d3.json("data/mineral.php", grafikMineral);
function grafikMineral(data) {
var valueLabelWidth = 50; // space reserved for value labels (right)
var barHeight = 38; // height of one bar
var barLabelWidth = 250; // space reserved for bar labels
var barLabelPadding = 20; // padding between bar and bar labels (left)
var gridLabelHeight = 18; // space reserved for gridline labels
var gridChartOffset = 10; // space between start of grid and first bar
var maxBarWidth = 800; // width of the bar with the max value


// data aggregation
var aggregatedData = d3.nest()
  .key(function(d) { return d['komoditas']; }) //group atas komoditas
  .rollup(function(d) {						   // untuk menggabungkan semua nama komoditas yang sama
    return {
		// menjumlahkan semua nilai pada komoditas yang memiliki nama yaang sama
      'value': d3.sum(d, function(e) { return parseFloat(e['nilai']); }) 
    };			
  })
  .entries(data);
 
// accessor functions 
var barLabel = function(d) { return d.key; };
var barValue = function(d) { return d.values.value; };
 
// sorting
var sortedData = aggregatedData.sort(function(a, b) {
	// me-sort nama-nama komoditas yang akan dimunculkan pada grafik  dari A ke Z
  return d3.ascending(barValue(a), barValue(b));  
}); 

// scales
//untuk membuat ukuran grafiknya, untuk panjang garis x dan y
var yScale = d3.scale.ordinal().domain(d3.range(0, sortedData.length)).rangeBands([0, sortedData.length * barHeight]);
var y = function(d, i) { return yScale(i); };
var yText = function(d, i) { return y(d, i) + yScale.rangeBand() / 2; };
var x = d3.scale.linear().domain([0, d3.max(sortedData, barValue)]).range([0, maxBarWidth]);

// svg container element
// code untuk menyisipkan grafik tersebut ke html, dengan memasukan code <div id="grafikMineral"></div> pada html
var chart = d3.select('#grafikMineral').append("svg")
  .attr('width', maxBarWidth + barLabelWidth + valueLabelWidth)
  .attr('height', gridLabelHeight + gridChartOffset + sortedData.length * barHeight);
  
  
// Untuk mengatur warna, alignment dan konfigurasi tampilan pada grafiknya  
// grid line labels
var gridContainer = chart.append('g')
  .attr('transform', 'translate(' + barLabelWidth + ',' + gridLabelHeight + ')'); 
gridContainer.selectAll("text").data(x.ticks(10)).enter().append("text")
  .attr("x", x)
  .attr("dy", -3)
  .attr("text-anchor", "middle")
  .text(String);
// vertical grid lines
gridContainer.selectAll("line").data(x.ticks(10)).enter().append("line")
  .attr("x1", x)
  .attr("x2", x)
  .attr("y1", 0)
  .attr("y2", yScale.rangeExtent()[1] + gridChartOffset)
  .style("stroke", "#ccc");
// bar labels
var labelsContainer = chart.append('g')
  .attr('transform', 'translate(' + (barLabelWidth - barLabelPadding) + ',' + (gridLabelHeight + gridChartOffset) + ')'); 
labelsContainer.selectAll('text').data(sortedData).enter().append('text')
  .attr('y', yText)
  .attr('stroke', 'none')
  .attr('fill', 'black')
  .attr("dy", ".35em") // vertical-align: middle
  .attr('text-anchor', 'end')
  .text(barLabel);
// bars
var barsContainer = chart.append('g')
  .attr('transform', 'translate(' + barLabelWidth + ',' + (gridLabelHeight + gridChartOffset) + ')'); 
barsContainer.selectAll("rect").data(sortedData).enter().append("rect")
  .attr('y', y)
  .attr('height', yScale.rangeBand())
  .attr('width', function(d) { return x(barValue(d)); })
  .attr('stroke', '#ecf0f1')
  .attr('fill', '#1abc9c');
// bar value labels
barsContainer.selectAll("text").data(sortedData).enter().append("text")
  .attr("x", function(d) { return x(barValue(d)); })
  .attr("y", yText)
  .attr("dx", 3) // padding-left
  .attr("dy", ".35em") // vertical-align: middle
  .attr("text-anchor", "start") // text-align: right
  .attr("fill", "black")
  .attr("stroke", "none")
  .text(function(d) { return d3.round(barValue(d), 2); });
// start line
barsContainer.append("line")
  .attr("y1", -gridChartOffset)
  .attr("y2", yScale.rangeExtent()[1] + gridChartOffset)
  .style("stroke", "#000");

}


		
var data = d3.json("data/mineral.php", grafikPerusahaan);
function grafikPerusahaan(data) {
var valueLabelWidth = 50; // space reserved for value labels (right)
var barHeight = 38; // height of one bar
var barLabelWidth = 250; // space reserved for bar labels
var barLabelPadding = 20; // padding between bar and bar labels (left)
var gridLabelHeight = 18; // space reserved for gridline labels
var gridChartOffset = 10; // space between start of grid and first bar
var maxBarWidth = 800; // width of the bar with the max value

// data aggregation
var aggregatedData = d3.nest()
  .key(function(d) { return d['nama_perusahaan']; })
  .rollup(function(d) {
    return {
      'value': d3.sum(d, function(e) { return parseFloat(e['tahun']); })
    };
  })
  .entries(data);
 
// accessor functions 
var barLabel = function(d) { return d.key; };
var barValue = function(d) { return d.values.value; };
 
// scales
var yScale = d3.scale.ordinal().domain(d3.range(0, aggregatedData.length)).rangeBands([0, aggregatedData.length * barHeight]);
var y = function(d, i) { return yScale(i); };
var yText = function(d, i) { return y(d, i) + yScale.rangeBand() / 2; };
var x = d3.scale.linear().domain([0, d3.max(aggregatedData, barValue)]).range([0, maxBarWidth]);
// svg container element
var chart = d3.select('#grafikPerusahaan').append("svg")
  .attr('width', maxBarWidth + barLabelWidth + valueLabelWidth)
  .attr('height', gridLabelHeight + gridChartOffset + aggregatedData.length * barHeight);
// grid line labels
var gridContainer = chart.append('g')
  .attr('transform', 'translate(' + barLabelWidth + ',' + gridLabelHeight + ')'); 
gridContainer.selectAll("text").data(x.ticks(10)).enter().append("text")
  .attr("x", x)
  .attr("dy", -3)
  .attr("text-anchor", "middle")
  .text(String);
// vertical grid lines
gridContainer.selectAll("line").data(x.ticks(10)).enter().append("line")
  .attr("x1", x)
  .attr("x2", x)
  .attr("y1", 0)
  .attr("y2", yScale.rangeExtent()[1] + gridChartOffset)
  .style("stroke", "#ccc");
// bar labels
var labelsContainer = chart.append('g')
  .attr('transform', 'translate(' + (barLabelWidth - barLabelPadding) + ',' + (gridLabelHeight + gridChartOffset) + ')'); 
labelsContainer.selectAll('text').data(aggregatedData).enter().append('text')
  .attr('y', yText)
  .attr('stroke', 'none')
  .attr('fill', 'black')
  .attr("dy", ".35em") // vertical-align: middle
  .attr('text-anchor', 'end')
  .text(barLabel);
// bars
var barsContainer = chart.append('g')
  .attr('transform', 'translate(' + barLabelWidth + ',' + (gridLabelHeight + gridChartOffset) + ')'); 
barsContainer.selectAll("rect").data(aggregatedData).enter().append("rect")
  .attr('y', y)
  .attr('height', yScale.rangeBand())
  .attr('width', function(d) { return x(barValue(d)); })
  .attr('stroke', '#34495e')
  .attr('fill', '#2980b9');
// bar value labels
barsContainer.selectAll("text").data(aggregatedData).enter().append("text")
  .attr("x", function(d) { return x(barValue(d)); })
  .attr("y", yText)
  .attr("dx", 3) // padding-left
  .attr("dy", ".55em") // vertical-align: middle
  .attr("text-anchor", "start") // text-align: right
  .attr("fill", "black")
  .attr("stroke", "none")
  .text(function(d) { return d3.round(barValue(d), 2); });
// start line
barsContainer.append("line")
  .attr("y1", -gridChartOffset)
  .attr("y2", yScale.rangeExtent()[1] + gridChartOffset)
  .style("stroke", "#000");

}


var data = d3.json("data/mineral.php", grafikTahun);
function grafikTahun(data) {

var valueLabelWidth = 50; // space reserved for value labels (right)
var barHeight = 38; // height of one bar
var barLabelWidth = 250; // space reserved for bar labels
var barLabelPadding = 20; // padding between bar and bar labels (left)
var gridLabelHeight = 18; // space reserved for gridline labels
var gridChartOffset = 10; // space between start of grid and first bar
var maxBarWidth = 800; // width of the bar with the max value

// data aggregation
var aggregatedData = d3.nest()
  .key(function(d) { return d['tahun']; })
  .rollup(function(d) {
    return {
      'value': d3.sum(d, function(e) { return parseFloat(e['nilai']); })
    };
  })
  .entries(data);
 
// accessor functions 
var barLabel = function(d) { return d.key; };
var barValue = function(d) { return d.values.value; };
 
// scales
var yScale = d3.scale.ordinal().domain(d3.range(0, aggregatedData.length)).rangeBands([0, aggregatedData.length * barHeight]);
var y = function(d, i) { return yScale(i); };
var yText = function(d, i) { return y(d, i) + yScale.rangeBand() / 2; };
var x = d3.scale.linear().domain([0, d3.max(aggregatedData, barValue)]).range([0, maxBarWidth]);
// svg container element
var chart = d3.select('#grafikTahun').append("svg")
  .attr('width', maxBarWidth + barLabelWidth + valueLabelWidth)
  .attr('height', gridLabelHeight + gridChartOffset + aggregatedData.length * barHeight);
// grid line labels
var gridContainer = chart.append('g')
  .attr('transform', 'translate(' + barLabelWidth + ',' + gridLabelHeight + ')'); 
gridContainer.selectAll("text").data(x.ticks(10)).enter().append("text")
  .attr("x", x)
  .attr("dy", -3)
  .attr("text-anchor", "middle")
  .text(String);
// vertical grid lines
gridContainer.selectAll("line").data(x.ticks(10)).enter().append("line")
  .attr("x1", x)
  .attr("x2", x)
  .attr("y1", 0)
  .attr("y2", yScale.rangeExtent()[1] + gridChartOffset)
  .style("stroke", "#ccc");
// bar labels
var labelsContainer = chart.append('g')
  .attr('transform', 'translate(' + (barLabelWidth - barLabelPadding) + ',' + (gridLabelHeight + gridChartOffset) + ')'); 
labelsContainer.selectAll('text').data(aggregatedData).enter().append('text')
  .attr('y', yText)
  .attr('stroke', 'none')
  .attr('fill', 'black')
  .attr("dy", ".35em") // vertical-align: middle
  .attr('text-anchor', 'end')
  .text(barLabel);
// bars
var barsContainer = chart.append('g')
  .attr('transform', 'translate(' + barLabelWidth + ',' + (gridLabelHeight + gridChartOffset) + ')'); 
barsContainer.selectAll("rect").data(aggregatedData).enter().append("rect")
  .attr('y', y)
  .attr('height', yScale.rangeBand())
  .attr('width', function(d) { return x(barValue(d)); })
  .attr('stroke', '#ecf0f1')
  .attr('fill', '#34495e');
// bar value labels
barsContainer.selectAll("text").data(aggregatedData).enter().append("text")
  .attr("x", function(d) { return x(barValue(d)); })
  .attr("y", yText)
  .attr("dx", 3) // padding-left
  .attr("dy", ".35em") // vertical-align: middle
  .attr("text-anchor", "start") // text-align: right
  .attr("fill", "black")
  .attr("stroke", "none")
  .text(function(d) { return d3.round(barValue(d), 2); });
// start line
barsContainer.append("line")
  .attr("y1", -gridChartOffset)
  .attr("y2", yScale.rangeExtent()[1] + gridChartOffset)
  .style("stroke", "#000");

}
