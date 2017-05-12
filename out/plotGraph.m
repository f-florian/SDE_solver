function plotGraph(name, tit="", out="")
  input=fopen(name, "r");
	[x,~,~]=fscanf(input,"%f %f",[2,Inf]);
	fclose(input);
	
  clf reset;
  hold on;
  plot(x(1,:),x(2,:));
  title(tit);
  legend("hide");
  print(out, "-dpdf");
  hold off;
endfunction
