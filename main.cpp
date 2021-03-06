
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "ResourcePath.hpp"

class Window {
    
public:
    
    Window();
    Window(const std::string& title_t, const sf::Vector2u& size_t);
    ~Window();
    
    void BeginDraw(); // Clear the window.
    void Draw(sf::Drawable& drawable);
    void EndDraw();
    // Display the changes.
    void Update();
    bool IsDone();
    
    sf::Vector2u GetWindowSize();
    
private:
    
    void Setup(const std::string& w_title, const sf::Vector2u& w_size);
    void Destroy();
    
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    
};

Window::Window() {
    Setup("Window", sf::Vector2u(800,600));
}

Window::Window(const std::string& w_title, const sf::Vector2u& w_size) {
    Setup(w_title,w_size);
}

Window::~Window() {
    Destroy();
}

void Window::Setup(const std::string& w_title, const sf::Vector2u& w_size) {
    
    m_windowTitle = w_title;
    m_windowSize = w_size;
    m_isDone = false;
    m_window.setFramerateLimit(60);
    m_window.create(sf::VideoMode(w_size.x, w_size.y), w_title);
    
}

void Window::Destroy() {
    m_window.close();
}

void Window::Update() {
    
    sf::Event event;
    
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_isDone = true;
        }
    }
    
}

void Window::BeginDraw() {
    m_window.clear(sf::Color::Black);
}

void Window::EndDraw() {
    m_window.display();
}

bool Window::IsDone() {
    return m_isDone;
    
}

sf::Vector2u Window::GetWindowSize() {
    return m_windowSize;
}

void Window::Draw(sf::Drawable& l_drawable) {
    m_window.draw(l_drawable);
}


class Hero {
    
public:
    
    void UpdateSprite();
    void SwitchSprite(sf::Sprite* spr1, sf::Sprite* spr2);
    
    void MoveHero(Window& window);
    void MoveHero_keypr(Window& window);
    
    void SetMovement(bool move, sf::Keyboard::Key key);
    
    sf::Vector2f getPosition();
    sf::Keyboard::Key getDirection();
    sf::Sprite& GetSprite();
    sf::Sprite* GetSprite_p();
    
    Hero() = delete;
    Hero(std::string name, std::string texture_name, std::string top_name,  std::string down_name,
    std::string left_name,  std::string right_name, std::string top2_name,  std::string down2_name,
    std::string left2_name,  std::string right2_name);
    
private:
    
    bool m_moving;
    std::string m_name;
    int m_which_sprite;
    
    sf::Keyboard::Key m_direction;
    
    sf::Texture m_hero_texture;
    sf::Texture m_hero_up_texture;
    sf::Texture m_hero_down_texture;
    sf::Texture m_hero_right_texture;
    sf::Texture m_hero_left_texture;
    
    sf::Texture m_hero_up_texture_2;
    sf::Texture m_hero_down_texture_2;
    sf::Texture m_hero_right_texture_2;
    sf::Texture m_hero_left_texture_2;
    
    sf::Sprite m_hero_sprite;
    sf::Sprite m_hero_up;
    sf::Sprite m_hero_down;
    sf::Sprite m_hero_right;
    sf::Sprite m_hero_left;
    
    sf::Sprite m_hero_up_2;
    sf::Sprite m_hero_down_2;
    sf::Sprite m_hero_right_2;
    sf::Sprite m_hero_left_2;
    
    sf::Sprite* m_hero_curSprite;

    
    sf::Clock m_switch_sprites;
    sf::Vector2f m_position;
    sf::Vector2f m_increment;
};

sf::Vector2f Hero::getPosition() {
    return m_position;
}

sf::Keyboard::Key Hero::getDirection() {
    return m_direction;
}

Hero::Hero(std::string name, std::string texture_name, std::string top_name,  std::string down_name,
            std::string left_name,  std::string right_name, std::string top2_name,  std::string down2_name,
            std::string left2_name,  std::string right2_name) {
    
    m_name = name;
    m_moving = false;
    m_which_sprite = 0;
    m_increment = sf::Vector2f(0.4f, 0.4f);
    
    m_hero_texture.loadFromFile(texture_name);
    
    m_hero_up_texture.loadFromFile(top_name);
    m_hero_down_texture.loadFromFile(down_name);
    m_hero_left_texture.loadFromFile(left_name);
    m_hero_right_texture.loadFromFile(right_name);
    
    m_hero_up_texture_2.loadFromFile(top2_name);
    m_hero_down_texture_2.loadFromFile(down2_name);
    m_hero_left_texture_2.loadFromFile(left2_name);
    m_hero_right_texture_2.loadFromFile(right2_name);
    
    //m_hero_sprite.setTexture(m_hero_left_texture);
    m_hero_up.setTexture(m_hero_up_texture);
    m_hero_down.setTexture(m_hero_down_texture);
    m_hero_left.setTexture(m_hero_left_texture);
    m_hero_right.setTexture(m_hero_right_texture);
    
    m_hero_up_2.setTexture(m_hero_up_texture_2);
    m_hero_down_2.setTexture(m_hero_down_texture_2);
    m_hero_left_2.setTexture(m_hero_left_texture_2);
    m_hero_right_2.setTexture(m_hero_right_texture_2);
    
    
    
    m_hero_sprite.setTexture(m_hero_up_texture); // setting the texture of our hero
    m_hero_curSprite = &m_hero_sprite;
    
    m_hero_sprite.setPosition(sf::Vector2f(100.f, 200.f));
    m_position = sf::Vector2f(m_hero_sprite.getPosition().x, m_hero_sprite.getPosition().y);
    m_switch_sprites.getElapsedTime();
}


void Hero::SwitchSprite(sf::Sprite* spr1, sf::Sprite* spr2) {
    
    if (m_moving == true) {
        if (m_switch_sprites.getElapsedTime() > sf::seconds(0.2f)) {
            m_switch_sprites.restart();
            
            if (m_which_sprite == 0) {
             //   m_hero_sprite.setTexture(m_hero_up_texture, true);
                spr1->setPosition(m_hero_curSprite->getPosition().x, m_hero_curSprite->getPosition().y);
                m_hero_curSprite = spr1;
                m_which_sprite = 1;
            } else if (m_which_sprite == 1) {
                //  std::cout <<" JJEFJ";
               // m_hero_sprite.setTexture(m_hero_up_texture_2, true);
                spr2->setPosition(m_hero_curSprite->getPosition().x, m_hero_curSprite->getPosition().y);
                m_hero_curSprite = spr2;
                m_which_sprite = 0;
            }
        }
        
    } else {
      //  m_hero_sprite.setTexture(m_hero_up_texture, true);
        spr1->setPosition(m_hero_curSprite->getPosition().x, m_hero_curSprite->getPosition().y);
        m_hero_curSprite = spr1;
    }
}



void Hero::UpdateSprite() {
    
    switch (m_direction) {
            
        case (sf::Keyboard::Up): {
            SwitchSprite(&m_hero_up, &m_hero_up_2);
            break;
        }
            
        case (sf::Keyboard::Down): {
             SwitchSprite(&m_hero_down, &m_hero_down_2);
            break;
        }
            
        case (sf::Keyboard::Left): {
             SwitchSprite(&m_hero_left, &m_hero_left_2);
            break;
        }
            
        case (sf::Keyboard::Right): {
             SwitchSprite(&m_hero_right, &m_hero_right_2);
            break;
        }
            
        default: {
            break;
        }
    }
}

void Hero::SetMovement(bool move, sf::Keyboard::Key key) {

    m_direction = key;
    m_moving = move;

}


sf::Sprite& Hero::GetSprite() {
    return m_hero_sprite;
}

sf::Sprite* Hero::GetSprite_p() {
    return m_hero_curSprite;
}

class BaseBlast;

class Blast {
    
public:
    
    Blast(Hero& hero, BaseBlast& base);
    void MoveBlast(Window& window);
    sf::Sprite* GetSprite_p();
    sf::Sprite* SetSprite();
    bool is_shot;
    
private:
    
    sf::Sprite m_blast_spr_up;
    sf::Sprite m_blast_spr_down;
    sf::Sprite m_blast_spr_left;
    sf::Sprite m_blast_spr_right;

    
    sf::Sprite* m_blast_curSprite;
    sf::Sprite m_blast_curSpr;
    
    sf::Vector2f m_speed;
    sf::Keyboard::Key m_direction;
    sf::Vector2f m_position;
    
    
};


class BaseBlast {
    
    public:
        
    sf::Clock GetCooldown();
    sf::Sprite* GiveSprite(sf::Keyboard::Key key);
    sf::Texture* GetTexture(sf::Keyboard::Key key);
    BaseBlast() = delete;
    BaseBlast(std::string texture_up, std::string texture_down, std::string texture_left,  std::string texture_right);
    int GetCount();
    void SetCount(int count);
    Blast** GetBlasts();
    
    sf::Time m_cooldown;
    sf::Clock m_coolclock;
    
    
    sf::Sprite m_blast_spr_up;
    sf::Sprite m_blast_spr_down;
    sf::Sprite m_blast_spr_left;
    sf::Sprite m_blast_spr_right;
        
    private:
        
    sf::Texture m_blast_texture_up;
    sf::Texture m_blast_texture_down;
    sf::Texture m_blast_texture_left;
    sf::Texture m_blast_texture_right;
    
    
    
    int m_count;
    
    Blast** m_blasts;
};


sf::Texture* BaseBlast::GetTexture(sf::Keyboard::Key key) {
    
    if (key == sf::Keyboard::Up) {
        return &m_blast_texture_up;
         }
         
         if (key == sf::Keyboard::Down) {
             return &m_blast_texture_down;
         }
         if (key == sf::Keyboard::Left) {
             return &m_blast_texture_left;
         }
         if (key == sf::Keyboard::Right) {
             return &m_blast_texture_right;
         }
    
}


int BaseBlast::GetCount() {
    return m_count;
}

sf::Clock BaseBlast::GetCooldown() {
    return m_coolclock;
}

sf::Sprite* BaseBlast::GiveSprite(sf::Keyboard::Key key) {
    
    if (key == sf::Keyboard::Up) {
           return &m_blast_spr_up;
       }
       
       if (key == sf::Keyboard::Down) {
           return &m_blast_spr_down;
       }
       if (key == sf::Keyboard::Left) {
           return &m_blast_spr_left;
       }
       if (key == sf::Keyboard::Right) {
           return &m_blast_spr_right;
       }
}

void BaseBlast::SetCount(int count) {
    m_count = count;
}

Blast** BaseBlast::GetBlasts() {
    return m_blasts;
}


sf::Sprite* Blast::SetSprite() {

    if (m_direction == sf::Keyboard::Up) {
        return &m_blast_spr_up;
    }
    
    if (m_direction == sf::Keyboard::Down) {
        return &m_blast_spr_down;
    }
    if (m_direction == sf::Keyboard::Left) {
        return &m_blast_spr_left;
    }
    if (m_direction == sf::Keyboard::Right) {
        return &m_blast_spr_right;
    }
    
}

sf::Sprite* Blast::GetSprite_p() {
    return m_blast_curSprite;
}

BaseBlast::BaseBlast(std::string texture_up, std::string texture_down, std::string texture_left,  std::string texture_right) {
    
    m_blast_texture_up.loadFromFile(texture_up);
    m_blast_texture_down.loadFromFile(texture_down);
    m_blast_texture_left.loadFromFile(texture_left);
    m_blast_texture_right.loadFromFile(texture_right);
    
    m_blast_spr_up.setTexture(m_blast_texture_up);
    m_blast_spr_down.setTexture(m_blast_texture_down);
    m_blast_spr_left.setTexture(m_blast_texture_left);
    m_blast_spr_right.setTexture(m_blast_texture_right);
    
    
    m_blasts = new Blast*[10];
    m_count = 0;
    m_cooldown = sf::seconds(0.5f);
    m_coolclock.getElapsedTime();
    
//    m_speed = sf::Vector2f(2.0f, 2.0f);
//    is_shot = false;
//
//    m_blast_curSprite = SetSprite();
//     m_blast_curSprite->setPosition(-100.f, -100.f);;
    
}

Blast::Blast(Hero& hero, BaseBlast& base_blast) {
    
    m_speed = sf::Vector2f(1.8f, 1.8f);
    m_direction = hero.getDirection();
    m_position = hero.getPosition();
    is_shot = true;
    
     m_blast_spr_up = base_blast.m_blast_spr_up;
     m_blast_spr_down = base_blast.m_blast_spr_down;
     m_blast_spr_left = base_blast.m_blast_spr_left;
     m_blast_spr_right = base_blast.m_blast_spr_right;
    
    std::cout << " created " << m_position.x << " " << m_position.y << std::endl;
    
    m_blast_curSprite = new sf::Sprite;
    m_blast_curSprite->setTexture(*(base_blast.GetTexture(m_direction)));
    //m_blast_curSpr = m_blast_spr_up;
    //m_blast_curSpr.setPosition(m_position.x, m_position.y); // fix
    m_blast_curSprite->setPosition(m_position.x, m_position.y); // fix
    
}

class Game {
    
public:
    
    Game();
    ~Game();
    void Update();
    void Render();
    void HandleInput();
    Window* GetWindow();
    Hero* GetHero();
    
private:
    
    Window m_window;
    Hero m_hero;
    BaseBlast m_base_blasts;
//    Blast m_blast;
};

Game::~Game() {
    
}

Window* Game::GetWindow() {
    return &m_window;
}

Hero* Game::GetHero() {
    return &m_hero;
}

//Blast* Game::GetBlast() {
//    return &m_blast;
//}

Game::Game(): m_window("Chapter 1", sf::Vector2u(1200,800)), m_hero("Shepard", "/Users/igorsidelnikov/Downloads/64723624.jpg", "/Users/igorsidelnikov/Downloads/top.png", "/Users/igorsidelnikov/Downloads/down.png", "/Users/igorsidelnikov/Downloads/left.png", "/Users/igorsidelnikov/Downloads/right.png", "/Users/igorsidelnikov/Downloads/top2.png", "/Users/igorsidelnikov/Downloads/down2.png", "/Users/igorsidelnikov/Downloads/left2.png", "/Users/igorsidelnikov/Downloads/right2.png"), m_base_blasts("/Users/igorsidelnikov/Downloads/blast_up.png", "/Users/igorsidelnikov/Downloads/blast_down.png", "/Users/igorsidelnikov/Downloads/blast_left.png", "/Users/igorsidelnikov/Downloads/blast_right.png") {
    
}

void Hero::MoveHero(Window& m_window) {
    
    sf::Vector2u l_windSize = m_window.GetWindowSize();
    sf::Vector2u l_textSize = m_hero_texture.getSize();

    if ((m_hero_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0)
        || (m_hero_sprite.getPosition().x < 0 && m_increment.x < 0)) {
        m_increment.x = -m_increment.x;
    }
    if ((m_hero_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0)
        || (m_hero_sprite.getPosition().y < 0 && m_increment.y < 0)){
        m_increment.y = -m_increment.y;
    }
    m_hero_sprite.setPosition(m_hero_sprite.getPosition().x + m_increment.x, m_hero_sprite.getPosition().y + m_increment.y);
}

void Blast::MoveBlast(Window& window) {
    
    sf::Vector2f cur_position = m_blast_curSprite->getPosition();
    
    if (m_direction == sf::Keyboard::Left) {
        m_blast_curSprite->setPosition(cur_position.x - m_speed.x, cur_position.y);
        m_position = sf::Vector2f(cur_position.x - m_speed.x, cur_position.y);
    }
    
    if (m_direction == sf::Keyboard::Right) {
       m_blast_curSprite->setPosition(cur_position.x + m_speed.x, cur_position.y);
       m_position = sf::Vector2f(cur_position.x + m_speed.x, cur_position.y);
    }
    
    if (m_direction == sf::Keyboard::Up) {
       m_blast_curSprite->setPosition(cur_position.x, cur_position.y - m_speed.y);
        m_position = sf::Vector2f(cur_position.x, cur_position.y - m_speed.y);
    }
    
    if (m_direction == sf::Keyboard::Down) {
       m_blast_curSprite->setPosition(cur_position.x, cur_position.y + m_speed.y);
        m_position = sf::Vector2f(cur_position.x, cur_position.y + m_speed.y);
    }
}

void Hero::MoveHero_keypr(Window &m_window) {
    
    sf::Vector2u l_windSize = m_window.GetWindowSize();
    sf::Vector2u l_textSize = m_hero_texture.getSize();
    
    if (m_moving == true) {
        
        sf::Vector2f cur_position = m_hero_curSprite->getPosition();
        
        if (m_direction == sf::Keyboard::Left) {
            m_hero_curSprite->setPosition(cur_position.x - m_increment.x, cur_position.y);
            m_position = sf::Vector2f(cur_position.x - m_increment.x, cur_position.y);
        }
        
        if (m_direction == sf::Keyboard::Right) {
           m_hero_curSprite->setPosition(cur_position.x + m_increment.x, cur_position.y);
           m_position = sf::Vector2f(cur_position.x + m_increment.x, cur_position.y);
        }
        
        if (m_direction == sf::Keyboard::Up) {
           m_hero_curSprite->setPosition(cur_position.x, cur_position.y - m_increment.y);
            m_position = sf::Vector2f(cur_position.x, cur_position.y - m_increment.y);
        }
        
        if (m_direction == sf::Keyboard::Down) {
           m_hero_curSprite->setPosition(cur_position.x, cur_position.y + m_increment.y);
            m_position = sf::Vector2f(cur_position.x, cur_position.y + m_increment.y);
        }
    }
    
}

void Game::Render(){
    
    m_window.BeginDraw();
    m_window.Draw(*(m_hero.GetSprite_p()));
    Blast** blasts = m_base_blasts.GetBlasts(); //todo in function
    for (int i = 0; i < m_base_blasts.GetCount(); ++i) {
        m_window.Draw(*(blasts[i]->GetSprite_p()));
       // std::cout << "MUST BE DRAWN " <<  i << std::endl;
    }
    m_window.EndDraw(); // Display.
}// Clear.



void Game::Update() {
    
    m_window.Update();
    // Update window events.
    Hero* myhero = GetHero();
    Blast** blasts = m_base_blasts.GetBlasts();
    
    myhero->MoveHero_keypr(m_window);

    for (int i = 0; i < m_base_blasts.GetCount(); ++i) {
        blasts[i]->MoveBlast(m_window);
    } // todo in function
    myhero->UpdateSprite();
    
  }

void Game::HandleInput() {
    
    Hero* myhero = GetHero();
    
    static sf::Keyboard::Key key; // TODO
    bool movement = false;
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            key = sf::Keyboard::Up;
            movement = true;
       //      std::cout << "Up";
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            key = sf::Keyboard::Down;
            movement = true;
         //    std::cout << "Down";
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            key = sf::Keyboard::Left;
            movement = true;
         //    std::cout << "Left";
        }
        
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            key = sf::Keyboard::Right;
            movement = true;
        }
        
    m_hero.SetMovement(movement, key);
    
    sf::Time time = m_base_blasts.m_coolclock.getElapsedTime();
    
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true) && (time > sf::seconds(0.3f)) ) { //TODO
        
        m_base_blasts.m_coolclock.restart();
        int count = m_base_blasts.GetCount();
        
       // std::cout << "count: " << count << "time " << time.asSeconds() <<  std::endl;
        Blast** blasts = m_base_blasts.GetBlasts(); // TODO in function which checks if the number of shots does not exceed max (e.g 30)
        blasts[count] = new Blast(*(myhero), m_base_blasts);
        m_base_blasts.SetCount(count + 1);
    }
}


int main(int, char const**) {
    
    
    Game game;
    // Creating our game object.
    
    while(game.GetWindow()->IsDone() == false) {
        // Game loop.
        game.HandleInput();
        game.Update();
        game.Render();
    }
    
    return EXIT_SUCCESS;
}
