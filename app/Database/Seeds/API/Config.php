<?php

namespace App\Database\Seeds\API;

use CodeIgniter\Database\Seeder;

class Config extends Seeder
{
    public function run()
    {
        $data = [
            'description' => 'POR DEFECTO',
            'water_porc'   => 50,
            'grain_porc'   => 60
        ];
        $this->db->table('config')->insert($data);
    }
}
