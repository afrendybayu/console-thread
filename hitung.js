var onload = 80;

// data parameter mesin
var data1= [{'id': 31111, 'value': 555.55, 'epoch': 1528250081},	// 0
			{'id': 31111, 'value': 111.11, 'epoch': 1528250082},	// 1
//			{'id': 31111, 'value': 444.44, 'epoch': 1528250083},	// 2
			{'id': 31111, 'value': 333.33, 'epoch': 1528250084},	// 3
//			{'id': 31111, 'value': 777.77, 'epoch': 1528250085},	// 4
			{'id': 31111, 'value': 222.22, 'epoch': 1528250086}];	// 5

// data load mesin
var data2= [{'id': 31115, 'value': 55.55, 'epoch': 1528250081},		// 0
			{'id': 31115, 'value': 86.11, 'epoch': 1528250082},		// 1
			{'id': 31115, 'value': 90.11, 'epoch': 1528250083},		// 2
//			{'id': 31115, 'value': 91.11, 'epoch': 1528250084},
			{'id': 31115, 'value': 90.77, 'epoch': 1528250085},		// 3
			{'id': 31115, 'value': 99.22, 'epoch': 1528250086}];


if (!data1) return;
if (!data2) return;
if (data1.length<=0)	return;
if (data2.length<=0)	return;

function mini(d1, d2) {
	return (d1.value>d2.value)?d2:d1;
}

function maxi(d1, d2) {
	return (d1.value>d2.value)?d1:d2;
}

var i=0, j=0, k=0, min, max, avg, tot=0, urut=0, x=0, y=0;
var nD1 = data1.length;
var nD2 = data2.length;
//**var loop1 = (nD1>nD2)?nD1:nD2;
//**var loop2 = (nD1>nD2)?nD2:nD1;
//**console.log("loop1: "+loop1+", loop2: "+loop2);

for (i=0; i<nD1; i++)	{
	for (j=k; j<nD2;j++)	{
//**		console.log("interasi "+(j+1)+", data1: "+data1[i].value+", data2: "+data2[i].value);
		if (data1[x].epoch==data2[y].epoch) {
			k = j+1;	// j+1
			break;
		}
	}
//**	console.log("nilai k: "+k);
	if (data2[y].value<onload)	{
		x++; y++;	
		continue;
	}
	console.log("diproses: "+data2[y].value+", nilai: "+data1[x].value);
	tot+=data1[i].value;
	if (urut==0)	{
		min = data1[x];
		max = data1[x];
	}
	else {
		min = mini(min, data1[x]);
		max = maxi(max, data1[x]);
	}
	console.log("++++++ d1: "+ data1[x].epoch+", d2: "+data2[y].epoch);
	urut++;
	console.log("x: "+x+", y: "+y+", min: "+min.value+", max: "+max.value);
	
	if (data1[x].epoch==data2[y].epoch) {
		x++;
		y++;
//**		console.log(">>> k: "+k+", x: "+x);
	} 
	else if (data1[x].epoch<data2[y].epoch)	{
		console.log("masuk kurang. d1: "+ data1[x].epoch+", d2: "+data2[y].epoch);
		x++;
	}
	else if (data1[x].epoch>data2[y].epoch)	{
		console.log("masuk lebih. d1: "+ data1[x].epoch+", d2: "+data2[y].epoch);
		y++;
		i--;
	}
//*/
}

//avg.value = (tot/urut);
avg = { id: data1[nD1-1].id, value: (tot/urut), epoch: data1[nD1-1].epoch };
console.log("-------------------------------------------");
console.log("min: "+min.value+", max: "+max.value+", avg: "+avg.value);


var ret = new Array(min, max, avg);
console.log(ret);
return ret;



