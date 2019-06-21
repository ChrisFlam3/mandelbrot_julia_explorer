#include <SFML\Graphics.hpp>
#include <iostream>
#include <string> 
#include <random>

using namespace std;

float calculateKernel(float x, float sigma)
{
	return 0.39894*exp(-0.5*x*x / (sigma*sigma)) / sigma;
}

int main() {
	sf::Clock clock;
	int precision = 1;
	float cx = 0;
	float cy = 0;
	int fractalType = 0;
	long double zoom = 1;
	sf::Vector2f fractalCenter=sf::Vector2f(0,0);
	sf::Vector2f fractalCenterUni = sf::Vector2f(0, 0);
	sf::Vector2f fractalCenterUniUni = sf::Vector2f(0, 0);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window", sf::Style::Default, settings);
	window.setFramerateLimit(60);
	sf::RectangleShape screen;
	screen.setSize(sf::Vector2f(1000, 1000));
	sf::Shader shader;
	shader.loadFromFile("mandelbrot.frag",sf::Shader::Fragment);
	shader.setUniform("zoom", (float)zoom);
	shader.setUniform("origin", fractalCenter);
	sf::Shader shaderIfs;
	shaderIfs.loadFromFile("flameIFS.frag", sf::Shader::Fragment);




	sf::Text zoomTxt;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	zoomTxt.setFont(font);
	zoomTxt.setString("Zoom X " + to_string(zoom) + " Mandelbrot");
	zoomTxt.setCharacterSize(24);
	zoomTxt.setFillColor(sf::Color::Black);
	string p;

	
	sf::Vector2i origin;
	bool mouseFlag = false;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code==sf::Keyboard::Add)
				{
					zoom *= 1.1;
					shader.setUniform("zoom",(float)zoom);
					if(fractalType==0)
						zoomTxt.setString("Zoom X " + to_string(zoom) + " Mandelbrot");
					else
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);
				}
				else if (event.key.code == sf::Keyboard::Subtract)
				{
					zoom /=1.1;
					shader.setUniform("zoom", (float)zoom);
					if(fractalType==0)
						zoomTxt.setString("Zoom X " + to_string(zoom) + " Mandelbrot");
					else
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);
				}
				else if (event.key.code == sf::Keyboard::J)
				{
					fractalType = 1;
					zoom = 1;
					fractalCenter = sf::Vector2f(0, 0);
					fractalCenterUni = sf::Vector2f(0, 0);
					fractalCenterUniUni = sf::Vector2f(0, 0);
					shader.loadFromFile("julia.frag", sf::Shader::Fragment);
					shader.setUniform("zoom", (float)zoom);
					shader.setUniform("origin", fractalCenter);
					shader.setUniform("cx", 0);
					shader.setUniform("cy", 0);
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);
					cx = 0;
					cy = 0;

					
				}
				else if (event.key.code == sf::Keyboard::M)
				{
					fractalType = 0;
					zoom = 1;
					fractalCenter = sf::Vector2f(0, 0);
					fractalCenterUni = sf::Vector2f(0, 0);
					fractalCenterUniUni = sf::Vector2f(0, 0);
					shader.loadFromFile("mandelbrot.frag", sf::Shader::Fragment);
					shader.setUniform("zoom", (float)zoom);
					shader.setUniform("origin", fractalCenter);
					zoomTxt.setString("Zoom X " + to_string(zoom)+" Mandelbrot");
				}
				else if (event.key.code == sf::Keyboard::Num1&&fractalType==1)
				{
					if(precision==1)
					cx -= 0.01;
					else
					cx -= 0.0001;
					shader.setUniform("cx", cx);
					zoomTxt.setString("Zoom X " + to_string(zoom)+" Julia x: "+to_string(cx)+"  y: " + to_string(cy)+p);
				}
				else if (event.key.code == sf::Keyboard::Num2&&fractalType == 1)
				{
					if (precision == 1)
						cx += 0.01;
					else
						cx += 0.0001;
					shader.setUniform("cx", cx);
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);
				}
				else if (event.key.code == sf::Keyboard::Num3&&fractalType == 1)
				{
					if (precision == 1)
						cy -= 0.01;
					else
						cy -= 0.0001;
					shader.setUniform("cy", cy);
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);
				}
				else if (event.key.code == sf::Keyboard::Num4&&fractalType == 1)
				{
					if (precision == 1)
						cy += 0.01;
					else
						cy += 0.0001;
					shader.setUniform("cy", cy);
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);
				}
				else if (event.key.code == sf::Keyboard::P&&fractalType == 1)
				{
					precision *= -1;
				
					if (precision == 1)
					p = "";
					else
					p = "  precision mode enabled";
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy) + p);
				}
				else if (event.key.code == sf::Keyboard::I) {

					float t = 0.1*1 - 1.0;

					sf::Transform am(cos(t*1.71 + 0.18), cos(t*1.31 + 3.18),0, cos(t*1.13 + 3.29), cos(t*1.44 + 4.21),0,0,0,1);
					sf::Transform bm(cos(t*2.57 + 1.66), cos(t*1.08 + 0.74), 0, cos(t*2.25 + 2.78), cos(t*1.23 + 1.29), 0, 0, 0, 1);
					sf::Transform cm(cos(t*1.15 + 6.33), cos(t*2.94 + 2.92), 0, cos(t*1.78 + 0.82), cos(t*2.58 + 2.36), 0, 0, 0, 1);
					sf::Transform dm(cos(t*1.42 + 4.89), cos(t*2.73 + 6.34), 0, cos(t*1.82 + 5.91), cos(t*1.21 + 3.84), 0, 0, 0, 1);

					sf::Vector2f at = sf::Vector2f(cos(t*2.13 + 0.94), cos(t*1.19 + 0.29))*(float)0.8;
					sf::Vector2f bt = sf::Vector2f(cos(t*1.09 + 5.25), cos(t*1.27 + 1.77))*(float)0.8;
					sf::Vector2f ct = sf::Vector2f(cos(t*2.76 + 4.39), cos(t*2.35 + 2.04))*(float)0.8;
					sf::Vector2f dt = sf::Vector2f(cos(t*1.42 + 4.71), cos(t*2.81 + 3.51))*(float)0.8;

					int max = 0;
					sf::Vector2f point = sf::Vector2f(0, 0);
					float cad = 0;
					auto histogram = new float[5001][5001][2]();
					std::random_device rd;
					std::default_random_engine e(rd());
					std::uniform_real_distribution<> d(0.0, 1.0);
					
					for (int i = 0; i < 2000000000; i++)
					{
				
						float result = d(e);


						if (result < 0.25) { point = am*point + at; cad =(cad+ 0.10)/2; }
						else if (result < 0.50) { point = bm*point + bt; cad = (cad+0.25)/2; }
						else if (result < 0.75) { point = cm*point + ct; cad = (cad+0.20)/2; }
						else { point = dm*point + dt; cad += 0.15; }

						//float zr = sqrtf(pow(point.x,2)+pow(point.y,2));
					//	float ar = atan2f(point.y, point.x) + zr*0.5;
					//	point = (float)2.0*sf::Vector2f(cos(ar), sin(ar)) / zr;
						point = 1 / (pow(point.x, 2) + pow(point.y, 2))*point;
					
						if (i > 20) {
								if (abs(point.x) > 5 || abs(point.y) > 5)
									continue;

							histogram[(int)((point.x+5)*500)][(int)((point.y+5)*500)][0] += 1;
							if (histogram[(int)((point.x + 5) * 500)][(int)((point.y + 5) * 500)][0] > max)
								max = histogram[(int)((point.x + 5) * 500)][(int)((point.y + 5) * 500)][0];
							histogram[(int)((point.x + 5) * 500)][(int)((point.y + 5) * 500)][1] = (histogram[(int)((point.x + 5) * 500)][(int)((point.y + 5) * 500)][1] + cad) / 2;
						}
						
					}
					
					//auto alpha=new float[1000][1000];
					sf::Image img;
					img.create(1000, 1000);
					float freq=0;
					float color=0;
					float alpha=0;
					auto freqArchive = new float[1000][1000];
					for (int i = 0; i < 1000; i++)
						for (int y = 0; y < 1000; y++) {
							for (int a = 0; a < 5; a++) {
								for (int b = 0; b < 5; b++) {
									freq = histogram[5 * y + b][5 * i + a][0];
									color= histogram[5 * y + b][5 * i + a][1];
									if(freq!=0)
									alpha += color*pow((log(freq) / log(max)), 1 / 2.2);
									freqArchive[y][i]+= histogram[5 * y + b][5 * i + a][0];
								}
							}
							//freq /= 16;
							//color /= 16;
							alpha /= 25;

				

							//alpha[y][i] = log(freq) / log(max);
							//float a = color * pow(alpha[y][i], 1 / 2.2);
							sf::Color col(alpha * 255, alpha * 255, alpha * 255, 255);
							img.setPixel(y, i, col);
					
						}


					//gaussian blur with density estimation
					for(int y=0;y<1000;y++)
						for (int x = 0; x < 1000; x++) {
							int kernelWidth = 9 / pow(freqArchive[x][y], 0.4);
							if (kernelWidth < 0)
								kernelWidth = 9;
							if (kernelWidth == 0)
								continue;

							int kernelSize = kernelWidth * 2+1;
							float* kernel=new float[kernelSize+1];
							float sigma = 6.;
							float Z = 0.0;
							float final_colour = 0;

							for (int j = 0; j <= kernelWidth; ++j)
							{
								kernel[kernelWidth + j] = kernel[kernelWidth - j] = calculateKernel(float(j), sigma);
							}

							for (int j = 0; j < kernelSize; ++j)
							{
								Z += kernel[j];
							}

					
							for (int i = -kernelWidth; i <= kernelWidth; ++i)
							{
								for (int j = -kernelWidth; j <= kernelWidth; ++j)
								{
									if (x + i < 0 || y + j < 0||x+1>999||y+j>999)
										continue;
									final_colour += kernel[kernelWidth + j] * kernel[kernelWidth + i]*img.getPixel(x + i, y + j).r;

								}
							}
							final_colour /= (Z*Z);
							sf::Color f(final_colour, final_colour, final_colour, 255);
							img.setPixel(x, y, f);










						}

					img.saveToFile("ifs.png");

				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					origin = sf::Mouse::getPosition(window);
					mouseFlag = true;
				}

			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouseFlag = false;
				}
			}
			if (event.type == sf::Event::MouseMoved&&mouseFlag==true)
			{
				
				if (0.01 / zoom > 0.000001) {
					fractalCenter.x += (origin.x - sf::Mouse::getPosition(window).x)*((double)0.01 / zoom);
					fractalCenter.y += (sf::Mouse::getPosition(window).y - origin.y)*((double)0.01 / zoom);
					origin = sf::Mouse::getPosition(window);
					shader.setUniform("origin", fractalCenter);
				}
				else if(zoom<10000000000){
					fractalCenterUni.x += (origin.x - sf::Mouse::getPosition(window).x) * 1000000 / zoom;
					fractalCenterUni.y += (sf::Mouse::getPosition(window).y - origin.y) * 1000000 / zoom;
					origin = sf::Mouse::getPosition(window);
					shader.setUniform("originUni", fractalCenterUni);
				}
				else {
					fractalCenterUniUni.x += (origin.x - sf::Mouse::getPosition(window).x) * 10000000000 / zoom;
					fractalCenterUniUni.y += (sf::Mouse::getPosition(window).y - origin.y) * 10000000000 / zoom;
					origin = sf::Mouse::getPosition(window);
					shader.setUniform("originUniUni", fractalCenterUniUni);
				}
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0) {
					zoom *= 1.1;
					shader.setUniform("zoom", (float)zoom);
					if(fractalType==0)
					zoomTxt.setString("Zoom X " + to_string(zoom)+" Mandelbrot");
					else
					zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);
				}
				else {
					zoom /= 1.1;
					shader.setUniform("zoom", (float)zoom);
					if (fractalType == 0)
						zoomTxt.setString("Zoom X " + to_string(zoom) + " Mandelbrot");
					else
						zoomTxt.setString("Zoom X " + to_string(zoom) + " Julia x: " + to_string(cx) + "  y: " + to_string(cy)+p);


				}







			}
		}
		window.clear();
		window.draw(screen, &shader);
		window.draw(zoomTxt);
		window.display();


	}
	
	return 0;
}