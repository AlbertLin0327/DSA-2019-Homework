#include <bits/stdc++.h>
using namespace std;
string words[] = {"auto", "bool", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "template", "union", "unsigned", "void", "volatile", "while"};

map <int, string> answer;
int main(){
	for(int a = 0; a < 26; a++){
		for(int b = 0; b < 26; b++){
			for(int c = 0; c < 26; c++){
				for(int d = 0; d < 26; d++){
					for(int e = 0; e < 26; e++){
						for(int f = 0; f < 26; f++){
							for(int g = 0; g < 26; g++){
								for(int h = 0; h < 26; h++){
									for(int i = 0; i < 26; i++){
										for(int j = 0; j < 26; j++){
											for(int k = 0; k < 26; k++){
												for(int l = 0; l < 26; l++){
													for(int m = 0; m < 26; m++){
														for(int n = 0; n < 26; n++){
															for(int o = 0; o < 26; o++){
																for(int p = 0; p < 26; p++){
																	for(int q = 0; q < 26; q++){
																		for(int r = 0; r < 26; r++){
																			for(int s = 0; s < 26; s++){
																				for(int t = 0; t < 26; t++){
																					for(int u = 0; u < 26; u++){
																						for(int v = 0; v < 26; v++){
																							for(int w = 0; w < 26; w++){
																								for(int x = 0; x < 26; x++){
																									for(int y = 0; y < 26; y++){
																										for(int z = 0; z < 26; z++){
																											for(auto word : words){
																												int sum = 0;
																												for(auto c : word){
																													if(c == 'a')
																														sum += a;
																													else if(c == 'b')
																														sum += b;
																													else if(c == 'c')
																														sum += c;
																													else if(c == 'd')
																														sum	+= d;
																													else if(c == 'e')
																														sum += e;
																													else if(c == 'f')
																														sum += f;
																													else if(c == 'g')
																														sum += g;
																													else if(c == 'h')
																														sum += h;
																													else if(c == 'i')
																														sum += i;
																													else if(c == 'j')
																														sum	+= j;
																													else if(c == 'k')
																														sum	+= k;
																													else if(c == 'l')
																														sum	+= l;
																													else if(c == 'm')
																														sum	+= m;
																													else if(c == 'n')
																														sum += n;
																													else if(c == 'o')
																														sum	+= o;
																													else if(c == 'p')
																														sum	+= p;
																													else if(c == 'q')
																														sum	+= q;
																													else if(c == 'r')
																														sum	+= r;
																													else if(c == 's')
																														sum	+= s;
																													else if(c == 't')
																														sum	+= t;
																													else if(c == 'u')
																														sum	+= u;
																													else if(c == 'v')
																														sum	+= v;
																													else if(c == 'w')
																														sum	+= w;
																													else if(c == 'x')
																														sum += x;
																													else if(c == 'y')
																														sum += y;
																													else if(c == 'z')
																														sum += z;
																												}
																												answer[sum % 32] = word;
																											}
																											if(answer.size() == 32){
																												cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << " " << h << " " << i << " " << j << " " << k << " " << l << " " << m << " " << n << " " << o << " " << p << " " << q << " " << r << " " << s << " " << t << " " << u << " " << v << " " << w << " " << x << " " << y << " " << z << endl;
																												for(auto n : answer){
																													cout << n.first << " " << n.second << endl;
																												}
																												exit(0);
																											}else{
																												answer.clear();
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
