#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

class texture
{
    public:
        //Initiates variables
        texture();

        //Deallocator
        ~texture();

        //Loads texture from image file
        bool Load_Image( SDL_Renderer* aRenderer , std::string aPath);

        //Loads texture from text
        bool Load_Text(std::string lText);

        //Erase existing texture
        void Free_Texture();

        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        void Render_Texture(SDL_Renderer* aRenderer , int x , int y , float size , SDL_Rect* clip);

    private:
        //Image texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;

};

texture::texture()
{
    mTexture=NULL;
    mWidth=0;
    mHeight=0;
}

texture::~texture()
{
   Free_Texture();
}

void texture::Free_Texture()
{
    if(mTexture!=NULL)
    {
        mTexture=NULL;
        mWidth=0;
        mHeight=0;
    }
}

bool texture::Load_Image( SDL_Renderer* aRenderer , std::string aPath )
{
    //Get rid of preexisting texture
	Free_Texture();

	//The final texture
	SDL_Texture* lTexture = NULL;

	//Load image at specified path
	SDL_Surface* lSurface = IMG_Load( aPath.c_str() );

	lTexture=SDL_CreateTextureFromSurface(aRenderer,lSurface);


	mTexture=lTexture;
	mHeight=lSurface->h;
	mWidth=lSurface->w;
	SDL_FreeSurface(lSurface);
	return mTexture != NULL;
}

void texture::Render_Texture(SDL_Renderer* aRenderer , int x , int y , float size , SDL_Rect* clip=NULL)
{
    int side=screenHeight;
    if(side>screenWidth)
        side=screenWidth;
    float ratio=1;
    int w,h;
    w=side*size;
    h=(side*size)/ratio;
    SDL_Rect renderQuad={x,y,w,h};
    SDL_RenderCopy(aRenderer,mTexture,clip,&renderQuad);
}

void texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

#endif // TEXTURE_H_INCLUDED
