<?php

namespace App\Database\Seeds;

use CodeIgniter\Database\Seeder;

class Database extends Seeder
{
    public function run()
    {
        $this->call('App\Database\Seeds\API\Config');
        $this->call('App\Database\Seeds\API\Type');
        $this->call('App\Database\Seeds\API\Logemail');
    }
}
