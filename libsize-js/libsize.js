"use strict";

var LSize = function() {
	this.type;
	this.opts ;
	this.precision;
	this.val;
	this.elements = [];

	this.useBytes();
	this.setPrecision(2);
	this.setOpt(this.OPTS.ABBRV);
}

LSize.prototype.TYPE = {
	BYTES: { idx: 0, str: "bytes" },
	BITS: { idx: 1, str: "bits" }
}

LSize.prototype.TABLE = [
	{ idx: 0, abbrv: "B", prfx: "" },
	{ idx: 1, abbrv: "KB", prfx: "Kilo" },
	{ idx: 2, abbrv: "MB", prfx: "Mega" },
	{ idx: 3, abbrv: "GB", prfx: "Giga" },
	{ idx: 4, abbrv: "TB", prfx: "Tera" },
	{ idx: 5, abbrv: "PB", prfx: "Peta" },
	{ idx: 6, abbrv: "EB", prfx: "Exa" },
	{ idx: 7, abbrv: "ZB", prfx: "Zetta" },
	{ idx: 8, abbrv: "YB", prfx: "Yotta" },
]

LSize.prototype.OPTS = {
	BYTES : 0x00,
	ABBRV : 0x01,
	WHOLE : 0x02,
	PLURAL : 0x04
}

LSize.prototype.setValue = function(value) {
	this.val = value;
}

LSize.prototype.setOpt = function(opt) {
	this.opts |= opt;
}

LSize.prototype.unsetOpt = function(opt) {
	this.opts &= ~opt;
}

LSize.prototype.useBytes = function() {
	this.type = this.TYPE.BYTES;
}

LSize.prototype.useBits = function() {
	this.type = this.TYPE.BITS;
}

LSize.prototype.setPrecision = function(precision) {
	this.precision = precision;
}

LSize.prototype.getConv = function() {
	return (this.type == this.TYPE.BITS ? 1000 : 1024);
}

LSize.prototype.guessSize = function() {
	var tres, j;

	for(var j = this.TABLE.length; j > 0; j--) {
		tres = Math.pow(this.getConv(), j);
		if(this.val >= tres) {
			return this.TABLE[j];
		}
	}

	return this.TABLE[0];
}

LSize.prototype.getAll = function() {
	var j;

	for(var j = 0; j < this.TABLE.length; j++) {
		var te = this.TABLE[j];
		this.getOne(te);
	}
}

LSize.prototype.getOne = function(size) {
	var lsze;

	lsze = new LSizeElement(this);
	lsze.getOne(size);

	this.elements[size.idx] = lsze;
}

LSize.prototype.dump = function() {
	for(var v in this.elements) {
		var el = this.elements[v];
		el.dump();
	}
}

LSize.prototype.format = function() {
	var lsze;

	lsze = new LSizeElement(this);
	lsze.guess();
	return lsze.result.toFixed(this.precision) + " " + lsze.str;
}



var LSizeElement = function(lsz) {
	this.lsz;
	this.size;
	this.str;
	this.val;
	this.div;
	this.result;

	this.lsz = lsz;
}

LSizeElement.prototype.guess = function() {
	var size;

	size = this.lsz.guessSize();
	this.getOne(size);

	return this;
}

LSizeElement.prototype.getOne = function(size) {
	this.size = size;
	this.val = this.lsz.val;

	this.div = Math.pow(this.lsz.getConv(), this.size.idx);
	this.result = this.val / this.div;

	if(this.lsz.opts & this.lsz.OPTS.WHOLE) {
		this.str = this.size.prfx + this.lsz.type.str;
	} else {
		this.str = this.size.abbrv;
	}
}

LSizeElement.prototype.dump = function() {
	console.log("size:"+JSON.stringify(this.size)+", str="+this.str+", val="+this.val+", div="+this.div+", result="+this.result);
}

module.exports = {
	LSize : LSize,
}
