var config = {
    type: Phaser.AUTO,
    width: 800,
    height: 600,
    physics: {
        default: 'arcade',
        arcade:{
            debug: false
        }

    },
    scene: {
        preload: preload,
        create: create,
        update: update
    }
};

var flag = 0;
var game = new Phaser.Game(config);
var spaceship;
var input;
var birds;
var bullets;

function preload ()
{
    console.log(this);
    this.load.image('space', "assets/space.png");
    this.load.image('spaceship', "assets/spaceship.png");
    this.load.spritesheet('bird', "assets/bird.png", {frameWidth: 598, frameHeight: 402});
    this.load.image('bullet', "assets/bullet.png");

}

function create()
{
    this.add.image(0, 0, 'space').setScale(1.8);
    spaceship = this.physics.add.image(400, 500, 'spaceship').setScale(0.5);
    spaceship.setCollideWorldBounds(true);

    birds = this.physics.add.group({
        key: 'bird',
        repeat: 200,
        setXY: {
            x: -20, y: -15
        }
    });

    bullets = this.physics.add.group({
        key: 'bullet'
    });
    bullets.setVelocityY(-200);

    this.anims.create(
        {
            key: 'bird',
            frames: this.anims.generateFrameNumbers('bird', {start:0, end: 7}),
            frameRate: 10,
            repeat: -1
        }
    );

    birds.children.iterate(function (bird){
        var x = Math.random() * -10000;
        var y = (Math.random() * 1000) % 300;
        bird.setPosition(x, y);
        bird.setScale(0.2);
        bird.anims.play('bird', true);
        bird.setVelocityX(100);
    })

    this.physics.add.collider(spaceship, birds);
    this.physics.add.overlap(bullets, birds, onCollision);


    input = this.input.keyboard.createCursorKeys();
}

function update()
{
    if(input.left.isDown){
        spaceship.setVelocityX(-100);
    }

    else if(input.right.isDown){
        spaceship.setVelocityX(100);
    }

    else if(input.down.isDown){
        spaceship.setVelocityY(100);
    }

    else if(input.up.isDown){
        spaceship.setVelocityY(-100);
    }

    else{
        spaceship.setVelocityX(0);
        spaceship.setVelocityY(0);
    }

    if(input.space.isDown){
        flag = 1;
    }
    else if(flag){
        fire(spaceship.x, spaceship.y);
        flag = 0;
    }
}

function fire(x , y){
    setTimeout(()=>{
        bullets.create(x, y, 'bullet').setScale(0.3);
        bullets.setVelocityY(-200);
    }, 200);

}

function onCollision(bullet, bird){
    bullet.disableBody(true, true);
    bird.disableBody(true, true);
}



