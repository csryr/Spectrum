#include "spectrum.h"

Spectrum::Spectrum(sf::RenderWindow &window) : window_(window) {}

void Spectrum::wavFFT()
{

	for (int i = 0; i < sampleChunk and i + samplesCovered < sampleCount; i++)
	{
		cx_in[i].r = samples[samplesCovered + i];
		cx_in[i].i = 0;
	}

	kiss_fft_cfg cfg = kiss_fft_alloc(sampleChunk, false, NULL, NULL);
	kiss_fft(cfg, cx_in, cx_out);
	kiss_fft_free(cfg);

	for (int i = 0; i < sampleChunk and i + samplesCovered < sampleCount; i++)
		currentSpectrum[i] = sqrt(pow(cx_out[i + 1].r, 2.0) + pow(cx_out[i + 1].i, 2.0));

	for (int i = 0; i < barsNum; i++)
	{

		currentSpectrum[i] *= 0.085 / sampleChunk;
	}

	for (int i = 0; i < barsNum; i++)
	{

		currentSpectrum[i] = (currentSpectrum[i] + prevSpectrum[i] + prevPrevSpectrum[i] + prevPrevPrevSpectrum[i]) / 4;
	}

	for (int i = 0; i < barsNum; i++)
	{
		prevSpectrum[i] = currentSpectrum[i];
	}

	for (int i = 0; i < barsNum; i++)
	{
		prevPrevSpectrum[i] = prevSpectrum[i];
	}

	for (int i = 0; i < barsNum; i++)
	{
		prevPrevPrevSpectrum[i] = prevPrevSpectrum[i];
	}

	samplesCovered += sampleChunk;
	dispSpectrum();
}

void Spectrum::loadBuffer(std::string audioFilePath)
{
	if (!buffer.loadFromFile(audioFilePath))
	{
	}
	else
	{
		song.setBuffer(buffer);
		sampleCount = buffer.getSampleCount();
		samples = buffer.getSamples();
	}
}

Spectrum::~Spectrum()
{
	delete[] cx_in;
	delete[] cx_out;
	delete[] currentSpectrum;
	delete[] prevSpectrum;
	delete[] prevPrevSpectrum;
	delete[] prevPrevPrevSpectrum;
}

void Spectrum::dispSpectrum()
{

	window_.clear();
	if (check == false)
	{
		song.play();
		check = true;
	}
	sf::sleep(fps);
	for (int i = 0; i < barsNum; i++)
	{

		sf::RectangleShape block(sf::Vector2f(20, std::min(468, currentSpectrum[i])));
		block.setPosition(i * 25 + 32, 580 - std::min(468, currentSpectrum[i]));
		block.setFillColor(sf::Color(138, 43, 226));
		window_.draw(block);
	}
	window_.display();
}