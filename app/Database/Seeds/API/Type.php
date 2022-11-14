<?php

namespace App\Database\Seeds\API;

use CodeIgniter\Database\Seeder;

class Type extends Seeder
{
    public function run()
    {
        $data = [
            [
                'description' => 'AGUA'
            ],
            [
                'description' => 'COMIDA'
            ],
        ];
        foreach ($data as $d)
            $this->db->table('type')->insert($d);
    }
}
