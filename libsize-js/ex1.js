#!/usr/bin/env node

var lsize = require("./libsize.js"),
	util = require("util");

var main = function(argc, argv) {
	var lsz = new lsize.LSize();
	for(var v in lsz.TABLE) {
		var te = lsz.TABLE[v];

		tres = Math.pow(1024, te.idx);
		tres -= 1;

		for(var j = 0; j < 3; j++) {
			lsz.setPrecision(j);
			lsz.setValue(tres);

			lsz.setOpt(lsz.OPTS.ABBRV);
			console.log("format("+tres+")="+lsz.format());
			lsz.unsetOpt(lsz.OPTS.ABBRV);

			lsz.setOpt(lsz.OPTS.WHOLE | ~lsz.OPTS.PLURAL);
			console.log("format("+tres+")="+lsz.format());

			lsz.setOpt(lsz.OPTS.WHOLE | lsz.OPTS.PLURAL);
			console.log("format("+tres+")="+lsz.format());

			lsz.useBits();
			console.log("format("+tres+")="+lsz.format());
			lsz.unsetOpt(lsz.OPTS.WHOLE | lsz.OPTS.PLURAL);
			lsz.useBytes();

			tres += 1;
		}
		console.log("");
	}


	for(var v in lsz.TABLE) {
		var te = lsz.TABLE[v];
		var tres = Math.pow(1024, te.idx) - 1;

		for(j = 0; j < 3; j++) {
			if(j == 2) {
				tres = tres + (tres / 2);
			}
			lsz.setPrecision(j);
			lsz.setValue(tres);
			lsz.getAll();
			lsz.dump();
			tres += 1;
			console.log("");
		}
		console.log("---------------------------------------");
	}
}

main(process.argv.length, process.argv);
